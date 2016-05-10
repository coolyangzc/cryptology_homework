#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
const int ROUNDS_PLUS = 11;

static uint8_t s_box[256] = {
	// 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, // 0
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, // 1
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, // 2
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, // 3
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, // 4
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, // 5
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, // 6
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, // 7
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, // 8
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, // 9
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, // a
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, // b
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, // c
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, // d
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, // e
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};// f

/*
 * Inverse S-box transformation table
 */
static uint8_t inv_s_box[256] = {
	// 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, // 0
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, // 1
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, // 2
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, // 3
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, // 4
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, // 5
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, // 6
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, // 7
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, // 8
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, // 9
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, // a
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, // b
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, // c
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, // d
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, // e
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};// f
    
uint8_t global_key[] = {
    0x3A,0xE1,0x15,0x62,
    0xA8,0xF3,0xC7,0x1A,
    0x2B,0xF6,0xDF,0xA1,
    0x50,0x9B,0xCA,0xF1}; 

uint8_t global_plaintext[] = {
    0x32,0x43,0xF6,0xA8,
    0x88,0x5A,0x30,0x8D,
    0x31,0x31,0x98,0xA2,
    0xE0,0x37,0x07,0x34};
    
uint8_t R[10][4] = {{0x01, 0x00, 0x00, 0x00},
                    {0x02, 0x00, 0x00, 0x00},
                    {0x04, 0x00, 0x00, 0x00},
                    {0x08, 0x00, 0x00, 0x00},
                    {0x10, 0x00, 0x00, 0x00},
                    {0x20, 0x00, 0x00, 0x00},
                    {0x40, 0x00, 0x00, 0x00},
                    {0x80, 0x00, 0x00, 0x00},
                    {0x1B, 0x00, 0x00, 0x00},
                    {0x36, 0x00, 0x00, 0x00}};
    
class AES_maker
{
public:
    uint8_t *key;
    uint8_t expand_key[ROUNDS_PLUS][4][4];
    uint8_t tmp[4];
    
    uint8_t *plaintext;
    uint8_t *cryptotext;
    uint8_t state[4][4];
    
    AES_maker()
    {
        key = global_key;
        plaintext = global_plaintext;
        cryptotext = new uint8_t[16];
    }
    
    //expand and using function
    
    void rot_word(uint8_t w[4]) 
    {
        uint8_t temp;
        temp = w[0];
        for (int i = 0; i < 3; i++) 
        {
            w[i] = w[i+1];
        }
        w[3] = temp;
    }
    
    void sub_word(uint8_t w[4]) 
    {
        for (int i = 0; i < 4; i++) {
            w[i] = s_box[16*((w[i] & 0xf0) >> 4) + (w[i] & 0x0f)];
        }
    }
    
    void coef_add(uint8_t a[4], uint8_t b[4], uint8_t d[4]) 
    {
        d[0] = a[0]^b[0];
        d[1] = a[1]^b[1];
        d[2] = a[2]^b[2];
        d[3] = a[3]^b[3];
    }
    
    void expand()
    {
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
        {
            expand_key[0][i][j] = key[4*i+j];
        }
        for(int i=1;i<ROUNDS_PLUS;i++)
        {
            for(int j=0;j<4;j++)
            {
                for(int k=0;k<4;k++)
                {
                    tmp[k] = expand_key[i][j-1][k];
                }
                if(j == 0)
                {
                    rot_word(tmp);
                    sub_word(tmp);
                    coef_add(tmp, R[i-1], tmp);
                }
                for(int k=0;k<4;k++)
                {
                    expand_key[i][j][k] = expand_key[i-1][j][k] ^ tmp[k];
                }
            }
        }
    }
    
    //making crypto
    void add_round_key(int r)
    {
        for (int c = 0; c < 4; c++)
            for (int k = 0; k < 4; k++)
            {
                state[k][c] = state[k][c]^expand_key[r][c][k];
            }
    }
    
    void sub_bytes() 
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                uint8_t row = (state[i][j] & 0xf0) >> 4;
                uint8_t col = state[i][j] & 0x0f;
                state[i][j] = s_box[16*row+col];
            }
        }
    }
    
    void shift_rows() 
    {
        for (int i = 0; i < 4; i++) {
            int s = 0;
            while (s < i) {
                uint8_t temp = state[i][0];
                for (int k = 1; k < 4; k++) {
                    state[i][k-1] = state[i][k];
                }
                state[i][3] = temp;
                s++;
            }
        }
    }
    
    uint8_t gmult(uint8_t a, uint8_t b) 
    {
        uint8_t p = 0, hbs = 0;
        for (int i = 0; i < 8; i++) {
            if (b & 1) {
                p ^= a;
            }

            hbs = a & 0x80;
            a <<= 1;
            if (hbs) a ^= 0x1b; // 0000 0001 0001 1011	
            b >>= 1;
        }
        return (uint8_t)p;
    }
    
    void coef_mult(uint8_t *a, uint8_t *b, uint8_t *d) 
    {
        d[0] = gmult(a[0],b[0])^gmult(a[3],b[1])^gmult(a[2],b[2])^gmult(a[1],b[3]);
        d[1] = gmult(a[1],b[0])^gmult(a[0],b[1])^gmult(a[3],b[2])^gmult(a[2],b[3]);
        d[2] = gmult(a[2],b[0])^gmult(a[1],b[1])^gmult(a[0],b[2])^gmult(a[3],b[3]);
        d[3] = gmult(a[3],b[0])^gmult(a[2],b[1])^gmult(a[1],b[2])^gmult(a[0],b[3]);
    }
    
    void mix_columns() 
    {
        uint8_t a[] = {0x02, 0x01, 0x01, 0x03}; // a(x) = {02} + {01}x + {01}x2 + {03}x3
        uint8_t col[4], res[4];
        for (int j = 0; j < 4; j++) 
        {
            for (int i = 0; i < 4; i++) 
            {
                col[i] = state[i][j];
            }
            coef_mult(a, col, res);
            for (int i = 0; i < 4; i++) 
            {
                state[i][j] = res[i];
            }
        }
    }
    
    void print_state()
    {
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
            {
                printf("%x ", state[j][i]);
            }
        printf("\n");
    }
    
    void cipher() 
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                state[i][j] = plaintext[i+4*j];
                printf("%x ", state[i][j]);
            }
        }
        
        printf("\n\n");

        add_round_key(0);
        print_state();
        for (int r = 1; r < ROUNDS_PLUS; r++) {
            sub_bytes();
            shift_rows();
            if(r != (ROUNDS_PLUS - 1)) mix_columns();
            add_round_key(r);
            print_state();
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cryptotext[i+4*j] = state[i][j];
            }
        }
    }
    
}aes;
    
int main()
{
    aes.expand();
    aes.cipher();
    printf("\n");
    for(int i=0;i<ROUNDS_PLUS;i++)
    {
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<4;k++)
            {
                printf("%x ", aes.expand_key[i][j][k]);
            }
        }
        printf("\n");
    }
    return 0;
}
