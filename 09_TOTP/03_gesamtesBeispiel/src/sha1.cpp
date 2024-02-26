#include "sha1.h"

#define SHA1_K0 0x5a827999
#define SHA1_K20 0x6ed9eba1
#define SHA1_K40 0x8f1bbcdc
#define SHA1_K60 0xca62c1d6

void Sha1::hashBlock()
{
	uint32_t a = state.w[0];
	uint32_t b = state.w[1];
	uint32_t c = state.w[2];
	uint32_t d = state.w[3];
	uint32_t e = state.w[4];
	uint32_t t;
	for (uint8_t i = 0; i < 80; i++)
	{
		if (i >= 16)
		{
			t = buffer.w[(i + 13) & 15] ^ buffer.w[(i + 8) & 15] ^ buffer.w[(i + 2) & 15] ^ buffer.w[i & 15];
			buffer.w[i & 15] = rol32(t, 1);
		}
		if (i < 20)
			t = (d ^ (b & (c ^ d))) + SHA1_K0;
		else if (i < 40)
			t = (b ^ c ^ d) + SHA1_K20;
		else if (i < 60)
			t = ((b & c) | (d & (b | c))) + SHA1_K40;
		else
			t = (b ^ c ^ d) + SHA1_K60;
		t += rol32(a, 5) + e + buffer.w[i & 15];
		e = d;
		d = c;
		c = rol32(b, 30);
		b = a;
		a = t;
	}
	state.w[0] += a;
	state.w[1] += b;
	state.w[2] += c;
	state.w[3] += d;
	state.w[4] += e;
}
