#include <stdint.h>
#include <stdio.h>
#include <assert.h>

const uint64_t upb=0x8000000000000000;
uint64_t umd=0xffffffffffffffff;
static uint64_t md(uint64_t a, uint64_t m){
	while(a<0){a+=m;}
	while(a>=m){
		uint64_t mp=m;
		while(mp<upb && mp<a){mp<<=1;}
		if(mp>=a){mp>>=1;}
		a-=mp;
	}
	return a;
}
	

static inline unsigned bit_of(uint64_t a, int i){
	return (a>>i)&1;
}

static uint64_t addmd(uint64_t a, uint64_t b, uint64_t m){
	uint64_t c=a+b;
	if(c>=a && c>=b){
		return md(c, m);
	}
	else{
		c=md(c+1, m);
		return addmd(c, umd, m);
	}
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m){
	umd=md(umd, m);
	a=md(a, m);
	b=md(b, m);
	uint64_t c=0;
	uint64_t tmp=b;
	for(int i=0; i<64; ++i){
		if(bit_of(a, i)==1){
			c=addmd(c, tmp, m);
		}
		tmp=addmd(tmp, tmp, m);
	}
	return c;
}
