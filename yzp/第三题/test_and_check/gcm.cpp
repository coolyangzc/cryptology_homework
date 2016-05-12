#include <cstdio>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
//#include <cmath>
#include <vector>
#include <map>
using namespace std;
typedef long long LL;
typedef pair<int,int> pint;
typedef pair<LL,LL> pll;
#define fi first
#define se second
typedef map<int,int> mapint;
typedef vector<int> vint;
typedef vector<vint> vintp;
#define rep(i,j,k) for (int i = (j);i <= (k);i ++)
#define repd(i,j,k) for (int i = (j);i >= (k);i --)
#define ran2 (rand() % 32000 * 32000 + rand() % 32000)
#define pb push_back
#define mp make_pair
#define SIZE(i) ((int)(i.size()))
int m,n,j,k,l,i,o,p,__t;
char ch;

void read(int &a) {
    for (ch = getchar();(ch < '0' || ch > '9') && (ch != '-');ch = getchar());
    if (ch == '-') a = 0,__t = -1; else a = ch - '0',__t = 1;
    for (ch = getchar();ch >= '0' && ch <= '9';ch = getchar()) a = a * 10 + ch - '0';
    a *= __t;
}

unsigned char sBox[] =
{ /*  0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f */ 
    0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76, /*0*/  
    0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0, /*1*/
    0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15, /*2*/ 
    0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75, /*3*/ 
    0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84, /*4*/ 
    0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf, /*5*/
    0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8, /*6*/  
    0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2, /*7*/ 
    0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73, /*8*/ 
    0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb, /*9*/ 
    0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79, /*a*/
    0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08, /*b*/
    0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a, /*c*/ 
    0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e, /*d*/
    0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf, /*e*/ 
    0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16  /*f*/
};
unsigned char invsBox[256] = 
{ /*  0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f  */  
    0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb, /*0*/ 
    0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb, /*1*/
    0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e, /*2*/ 
    0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25, /*3*/ 
    0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92, /*4*/ 
    0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84, /*5*/ 
    0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06, /*6*/ 
    0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b, /*7*/
    0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73, /*8*/ 
    0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e, /*9*/
    0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b, /*a*/
    0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4, /*b*/ 
    0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f, /*c*/ 
    0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef, /*d*/ 
    0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61, /*e*/ 
    0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d  /*f*/
}; 

#define BYTE(x, y) ((x << (8 * y)) >> 24)
#define BIT(x) (1 << (x))

void SETBYTE(unsigned int &x, int y, unsigned int z) {
    unsigned int pre = (y == 0 ? 0 : (x >> (32 - 8 * y))) << (y == 0 ? 0 : (32 - 8 * y));
    unsigned int suf = (y == 3) ? 0 : ((x << (8 + 8 * y)) >> (8 + 8 * y));
    x = pre | suf | (z << (24 - 8 * y)); 
}



void sub_byte(unsigned int *x, bool rev = 0) {
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j ++)
            if (rev == false)
                SETBYTE(x[i], j, sBox[BYTE(x[i], j)]);
            else
                SETBYTE(x[i], j, invsBox[BYTE(x[i], j)]);
}

unsigned int sub_byte_single(unsigned int x) {
    for (int i = 0; i < 4; i ++)
        SETBYTE(x, i, sBox[BYTE(x, i)]);
    return x;
}

unsigned int ROTL(unsigned int x, int l) {
    return (x << l) | (x >> (32 - l));
}

unsigned int ROTR(unsigned int x, int l) {
    return (x >> l) | (x << (32 - l));
}

unsigned int shift_row_temp[4];
void shift_row(unsigned int *x, bool rev = 0) {
    memset(shift_row_temp, 0, sizeof(unsigned int) * 4);
    for (int i = 0; i < 4; i ++)
        for (int j = 0; j < 4; j ++)
        if (rev == 0)
            SETBYTE(shift_row_temp[i], j, BYTE(x[(i + j) % 4], j));
        else 
            SETBYTE(shift_row_temp[i], j, BYTE(x[(i - j + 4) % 4], j));
    memcpy(x, shift_row_temp, sizeof (unsigned int) * 4);
}

unsigned int field_mul(unsigned int x, unsigned int y) {
    unsigned int val = 0;
    for (int i = 0; i < 8; i ++)
        for (int j = 0; j < 8; j ++)
            if (((x & BIT(i)) > 0) && (y & BIT(j)) > 0) {
                val ^= BIT((i + j));
            }
    for (int digit = 14; digit >= 8; digit --)
        if ((val & BIT(digit)) > 0) {
            val ^= BIT(digit) | BIT(digit - 4) | BIT(digit - 5) | BIT(digit - 7) | BIT(digit - 8);  
        }
    return val;
}

unsigned int mix_columns_temp[4], mix_columns_res[4];
void mix_columns(unsigned int *x, bool rev = false) {
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++)
            mix_columns_temp[j] = BYTE(x[i], j);

        for (int j = 0; j < 4; j ++)
            if (rev == 0)
                mix_columns_res[j] = field_mul(2, mix_columns_temp[j]) 
                ^ field_mul(3, mix_columns_temp[(j + 1) % 4]) ^
                mix_columns_temp[(j + 2) % 4] ^ mix_columns_temp[(j + 3) % 4];
            else
                mix_columns_res[j] = field_mul(0x0e, mix_columns_temp[j]) 
                ^ field_mul(0x0b, mix_columns_temp[(j + 1) % 4]) 
                ^ field_mul(0x0d, mix_columns_temp[(j + 2) % 4]) 
                ^ field_mul(0x09, mix_columns_temp[(j + 3) % 4]);
        x[i] = (BYTE(mix_columns_res[0], 3) << 24) |
                (BYTE(mix_columns_res[1], 3) << 16) |
                (BYTE(mix_columns_res[2], 3) << 8) |
                (BYTE(mix_columns_res[3], 3));
    }
    
}



void key_expand(unsigned int *key, vector<unsigned int> &keys) {
    unsigned rcon[11] = {0, 0x01000000, 0x02000000, 0x04000000, 0x08000000,
        0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000};
    keys.clear();
    for (int i = 0; i < 4; i ++)
        keys.pb(key[i]);
    for (int i = 4; i < 44; i ++) {
        unsigned int temp = keys[i - 1];
        if (i % 4 == 0) {
            temp = sub_byte_single(ROTL(temp, 8)) ^ rcon[i / 4];
        }
        keys.pb(temp ^ keys[i - 4]);
    }
}

void convert_string(string &buff, vector<unsigned int> &inputbuff) {
    inputbuff.clear();
    int len = buff.size();
    unsigned int val = 0;
    for (int i = 0; i < len; i ++) {
        val = (val << 8) + (int(buff[i]));
        if (i % 4 == 3) {
            inputbuff.pb(val);
            val = 0;
            if (i == len - 1) {
                inputbuff.pb(((unsigned int) 1) << 31);
            }
        } else
        if (i == len - 1) {
            int shift_digit = (3 - (i % len)) * 8;
            inputbuff.pb((val << shift_digit) | (1 << (shift_digit - 1)));
        }
    }
}

vector<unsigned int> keys;

void aes(unsigned int *content, unsigned int *key) {
    key_expand(key, keys);
    // for (int i = 0; i < keys.size(); i ++)
        // printf("key[%d] = 0x%08x\n", i, keys[i]);

    for (int j = 0; j < 4; j ++)
        content[j % 4] ^= keys[j];
    for (int i = 1; i <= 10; i ++) {
        sub_byte(content);
        shift_row(content);
        if (i != 10)
            mix_columns(content);
        for (int j = 4 * i; j < 4 * i + 4; j ++)
            content[j % 4] ^= keys[j];
    }

    // printf("final result = 0x%08x %08x %08x %08x\n", content[0], content[1], content[2], content[3]);
}

void inc32(unsigned int *a) {
    a[3] += 1;
    a[2] += (a[3] == 0);
    a[1] += (a[3] == 0 && a[2] == 0);
    a[0] += (a[3] == 0 && a[2] == 0 && a[1] == 0);
}

class Bitstream {
public:
    unsigned char *v;
    int len;
    Bitstream(string &init) {
        v = (unsigned char *) malloc(init.size() * 8);
        int index = 0;
        len = init.size() * 8;
        for (int i = 0; i < init.size(); i ++)
            for (int j = 7; j >= 0; j --)
                v[index ++] = ((init[i] & BIT(j)) > 0 ? 1 : 0);
    }
    void assign(int len_) {
        v = (unsigned char *) malloc(len_);
        len = len_;
        memset(v, 0, len);
    }
    Bitstream(int len_) {
        assign(len_);
    }

    void enlarge(int n) {
        unsigned char *temp = (unsigned char *) malloc(n + len);
        memcpy(temp, v, len);
        len += n;
        free(v);
        v = temp;
    }

    void append(Bitstream &n) {
        int index = len;
        enlarge(n.len);
        for (int i = 0; i < n.len; i ++)
            v[index ++] = n.v[i];
    }

    void append(unsigned char ch, int size) {
        int index = len;
        enlarge(size);
        for (int i = 0; i < size; i ++)
            v[index ++] = ch;
    }

    void append_int64(unsigned long long a) {
        int index = len;
        enlarge(64);
        for (int i = 63; i >= 0; i --)
            v[index ++] = (a & (((unsigned long long)1) << i)) > 0 ? 1 : 0;
    }

    void append_int32(unsigned int a) {
        int index = len;
        enlarge(32);
        for (int i = 31; i >= 0; i --)
            v[index ++] = (a & (((unsigned long long)1) << i)) > 0 ? 1 : 0;
    }

    void print_hex(){
        printf("%d 0x", len);
        for (int i = 0; i < len; i += 8) {
            unsigned char a = 0;
            for (int j = 0; j < 8; j ++)
                a |= (1 << (7 - j)) * v[i + j];
            printf("%02x", a);
        }
        printf("\n");
    }

    void append_hexstr(string &s) {
        int index = len;
        enlarge(s.length() * 4);
        for (int i = 0; i < s.length(); i ++) {
            int val = 0;
            if (s[i] >= '0' && s[i] <= '9') 
                val = s[i] - '0';
            else
                val = s[i] - 'a' + 10;

            for (int j = 3; j >= 0; j --)
                v[index ++] = (val & (BIT(j))) > 0 ? 1 : 0;
        }
    }

    void append_asciistr(string &s) {
        int index = len;
        enlarge(s.length() * 8);
        for (int i = 0; i < s.length(); i ++) {
            int val = s[i];
            for (int j = 7; j >= 0; j --)
                v[index ++] = (val & (BIT(j))) > 0 ? 1 : 0;
        }   
    }

    ~Bitstream() {
        // printf("free %d\n", len);
        free(v);
    }
};

void GCTR(unsigned int *icb, Bitstream *text, Bitstream *result, unsigned int *key) {
    int n = text->len / 128 + (text->len % 128 != 0);
    unsigned int cipher_icb[4];

    for (int i = 0; i < n; i ++) {
        if (i != 0)
            inc32(icb);
        memcpy(cipher_icb, icb, sizeof(unsigned int) * 4);
        aes(cipher_icb, key);
        if (i != n - 1) {
            int index = i * 128;
            for (int k = 0; k < 4; k ++)
                for (int j = 31; j >= 0; j --) {
                    result->v[index] = text->v[index] ^ ((cipher_icb[k] & BIT(j)) > 0 ? 1 : 0);
                    index += 1;
                }
        } else {
            int index = i * 128;
            for (int k = 0; k < 4; k ++)
                for (int j = 31; j >= 0; j --) {
                    if (index == text->len)
                        break;
                    result->v[index] = text->v[index] ^ ((cipher_icb[k] & BIT(j)) > 0 ? 1 : 0);
                    index += 1;
                }
        }
    }
}

void GHASH(Bitstream &addi_i, Bitstream &ciph_i, unsigned int* hash_key, Bitstream &ret) {
    printf("GHASH function\n");
    Bitstream Z(128);
    int lena = addi_i.len + (addi_i.len % 128 != 0) * (128 - addi_i.len % 128);
    int lenc = ciph_i.len + (ciph_i.len % 128 != 0) * (128 - ciph_i.len % 128);
    int len = lena + lenc + 128;
    int n = len / 128;
    Bitstream X(0);
    X.append(addi_i);
    X.append(0, lena - addi_i.len);
    
    X.append(ciph_i);
    X.append(0, lenc - ciph_i.len);
    
    X.append_int64((unsigned long long)addi_i.len);
    printf("    |A| = %64x\n", addi_i.len);
    X.append_int64((unsigned long long)ciph_i.len);
    printf("    |C| = %64x\n", ciph_i.len);

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < 128; j ++)
            ret.v[j] ^= X.v[128 * i + j];
        // multi
        // memcpy(V.v, hash_key, 128); //H = Y
        Bitstream V(0);
        V.append_int32(hash_key[0]);
        V.append_int32(hash_key[1]);
        V.append_int32(hash_key[2]);
        V.append_int32(hash_key[3]);
        memset(Z.v, 0, 128);

        for (int j = 0; j < 128; j ++) {
            if (ret.v[j] == 1)
                for (int k = 0; k < 128; k ++)
                    Z.v[k] ^= V.v[k];
            bool R_xor = (V.v[127] == 1);
            for (int k = 127; k > 0; k --)
                V.v[k] = V.v[k - 1];
            V.v[0] = 0;
            if (R_xor) {
                V.v[0] ^= 1; V.v[1] ^= 1; V.v[2] ^= 1; V.v[7] ^= 1;
            }

        }
        memcpy(ret.v, Z.v, 128);
    }
    printf("    additional text\n    ");
    addi_i.print_hex();
    printf("    plain text\n    ");
    ciph_i.print_hex();
    printf("    GHASH answer\n    ");
    ret.print_hex();
    // return ret;
}

int main() {
    // freopen("sha256.in","r",stdin);
    //freopen("sha256.out","w",stdout);

    // string buff = "2013011402qiandichen";
    string buff = "";
    // vector<unsigned int> inputbuff;
    // convert_string(buff, inputbuff);
    // while (inputbuff.size() % 4 != 0)
        // inputbuff.pb(0);
    // unsigned int content[4] = {0x3243F6A8, 0x885A308D, 0x313198A2, 0xE0370734};
    // unsigned int key[4] = {0x3AE11562, 0xA8F3C71A, 0x2BF6DFA1, 0x509BCAF1};
    // unsigned int key[4] = {0, 0, 0, 0};
    /* 
        This parameters can be changed.
        key : AES-key 128 bytes
        IV : 96 bytes for gcm mode
        hash_key : 128 bytes for GHASH function
        plain_text : the string that want to be encode
        addition_text : the string of additional text
    */
    unsigned int key[4] = {0x3AE11562, 0xA8F3C71A, 0x2BF6DFA1, 0x509BCAF1};
    // unsigned int IV[4] = {0xcafebabe, 0xfacedbad, 0xdecaf888, 0};
    unsigned int IV[4] = {0, 0, 0, 0};
    // unsigned int hash_key[4] = {0x66e94bd4, 0xef8a2c3b, 0x884cfa59, 0xca342b2e};
    // unsigned int hash_key[4] = {0xb83b5337, 0x08bf535d, 0x0aa6e529, 0x80d53b78};
    IV[3] = 1;
    unsigned int hash_key[4] = {0, 0, 0, 0};
    // Bitstream plain_text = Bitstream(buff);
    Bitstream plain_text = Bitstream(0);
    // string plain_text_str = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b391aafd255";
    // plain_text.append_hexstr(plain_text_str);
    
    string plain_text_str = "";
    plain_text.append_asciistr(plain_text_str);
    
    // plain_text.append(0, 128);  

    // gsm(content, key);
    // unsigned int key[4] = {0x61616161, 0x61616161, 0x61616161, 0x61616161};

    aes(hash_key, key);

    unsigned int j0[4] = {0, 0, 0, 0};
    memcpy(j0, IV, sizeof(unsigned int) * 4);

    Bitstream gctr_bits = Bitstream(plain_text.len);
    Bitstream addition_text = Bitstream(0);
    // string add_text_str = "feedfacedeadbeeffeedfacedeadbeefabaddad2";
    string add_text_str = "qiandichen2013011402";
    addition_text.append_asciistr(add_text_str);

    inc32(j0);
    GCTR(j0, &plain_text, &gctr_bits, key);
    Bitstream S(128);
    GHASH(addition_text, gctr_bits, hash_key, S);
    Bitstream final_res(S.len);
    GCTR(IV, &S, &final_res, key);
    printf("T = \n");
    final_res.print_hex();


    
    // for (int i = 0; i < inputbuff.size(); i ++)
        // printf("0x%08x ", inputbuff[i]);
    // printf("%08x\n", field_mul(131, 87));
    //fclose(stdin); fclose(stdout);
}
