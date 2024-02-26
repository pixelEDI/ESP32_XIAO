#ifndef SHA1_H
#define SHA1_H

#include <inttypes.h>
#include <string.h>

#if defined(__AVR__)
#include <avr/pgmspace.h>
#define PROGMEM_IDENTIFIER PROGMEM
#define PROG_MEM_COPY(dst,src,sz) memcpy_P((dst),(src),(sz));
#else //Non Avr eg.ESP32
#define PROGMEM_IDENTIFIER
#define PROG_MEM_COPY(dst,src,sz) memcpy((dst),(src),(sz));
#endif

#define HASH_LENGTH 20
#define BLOCK_LENGTH 64

#define HMAC_IPAD 0x36
#define HMAC_OPAD 0x5c

union _buffer 
	{
	uint8_t b[BLOCK_LENGTH];
	uint32_t w[BLOCK_LENGTH/4];
	};
union _state 
	{
	uint8_t b[HASH_LENGTH];
	uint32_t w[HASH_LENGTH/4];
	};

const uint8_t sha1InitState[] PROGMEM_IDENTIFIER =
	{
	0x01,0x23,0x45,0x67, // H0
	0x89,0xab,0xcd,0xef, // H1
	0xfe,0xdc,0xba,0x98, // H2
	0x76,0x54,0x32,0x10, // H3
	0xf0,0xe1,0xd2,0xc3  // H4
	};

class Sha1
{
public:
	Sha1():byte_count(0),buf_offset(0){}
public:
  void init()
		{
		byte_count = 0;
		buf_offset = 0;
		PROG_MEM_COPY(state.b,sha1InitState,HASH_LENGTH);
		}
	void init_hmac(const uint8_t* key,int key_len)
		{
		memset(key_buf,0,BLOCK_LENGTH);
		if(key_len>BLOCK_LENGTH) // Hash long keys
			{	
			init();
			for(;key_len--;) 
				write(*key++);
			memcpy(key_buf,end(),HASH_LENGTH);
			} 
		else	// Block length keys are used as is	
			memcpy(key_buf,key,key_len);
		// Start inner hash
		init();
		for(uint8_t i=0; i<BLOCK_LENGTH; i++)
			write(key_buf[i] ^ HMAC_IPAD);
		}
public:
	void write(uint8_t b)
		{
		byte_count++;
		add(b);
		}
	void write(const uint8_t *buffer,size_t len)
		{
		if(buffer==NULL)return; //sanity check
		for(;len--;) 
			write(*buffer++);
		}
	void write(const char *str) //MUST be string
		{
		if(str==NULL)return; //sanity check
		while(*str) 
			write(*str++);
		}
public:
	const uint8_t* end()
		{ 
		pad(); // Pad to complete the last block
		// Swap byte order back
		for(uint8_t i=0; i<(HASH_LENGTH/4); i++) 
			{
			uint32_t a=state.w[i];
			uint32_t b=a<<24;
			b|=(a<<8) & 0x00ff0000;
			b|=(a>>8) & 0x0000ff00;
			b|=a>>24;
			state.w[i]=b;
			}  
		return state.b;	//Return pointer to hash
		}
	const uint8_t* end_hmac() 
		{
		//Complete inner hash
		memcpy(inner_hash,end(),HASH_LENGTH);
		//Calculate outer hash
		init();
		uint8_t i;
		for(i=0; i<BLOCK_LENGTH; i++)write(key_buf[i] ^ HMAC_OPAD);
		for(i=0; i<HASH_LENGTH; i++)write(inner_hash[i]);
		return end();
		}
private:
	uint32_t rol32(uint32_t num,uint8_t bits){return (num<<bits) | (num>>(32-bits));}
	void add(uint8_t data)
		{
		buffer.b[buf_offset ^ 3] = data;
		buf_offset++;
		if(buf_offset==BLOCK_LENGTH) 
			{
			hashBlock();
			buf_offset=0;
			}
		}
	void pad()
		{
		// Implement SHA-1 padding (fips180-2 �5.1.1)
		// Pad with 0x80 followed by 0x00 until the end of the block
		add(0x80);
		while(buf_offset!=(BLOCK_LENGTH-8))
			add(0x00);
		// Append length in bits is the last 8 bytes
		// We're only using 32 bit lengths but SHA-1 supports 64 bit lengths
		// So zero pad the top bits 
		//Shifting to multiply by 8 as SHA-1 supports bitstreams as well as bytes
		add(0);	
		add(0);	
		add(0);
		add(byte_count >> 29); 
		add(byte_count >> 21); 
		add(byte_count >> 13);
		add(byte_count >> 5);
		add(byte_count << 3);
		}	
	void hashBlock();
private:
	_buffer buffer;
	uint8_t buf_offset;
	_state	state;
	uint32_t byte_count;
	uint8_t key_buf[BLOCK_LENGTH];
	uint8_t inner_hash[HASH_LENGTH];
};

#endif
