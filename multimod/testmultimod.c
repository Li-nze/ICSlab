#include <stdint.h>
#include <stdio.h>
#include <assert.h>

/*
uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  return (a * b) % m; // buggy
}
*/

const uint64_t upb=0x8000000000000000;
uint64_t umod=0xffffffffffffffff;
static uint64_t mod(uint64_t a, uint64_t m){
	//printf("%lu %lu\n", a, m);
	if(a<m){return a;}
	while(a<0){a+=m;}
	while(a>=m){
		//printf("a\n");
		uint64_t mp=m;
		while(mp<upb && mp<a){mp<<=1;}
		if(mp>=a && mp!=1){mp>>=1;}
		a-=mp;
	}
	return a;
}
/*
static uint64_t mod(uint64_t a, uint64_t m){
	while(a<0){a+=m;}
	//printf("%lu\n%lu\n", a, m);
	while(a>=m){
		a-=m;
	}
	//printf("%lu\n%lu\n", a, m);
	return a;
}
*/
static uint64_t pow2(uint64_t m){
	if(m==0){return 0;}
	uint64_t f=0;
	uint64_t count=0;
	while(m>0){
		if(!f){++count;}
		uint64_t a=m&1;
		if(!f && a){f=1;}
		if(f && a){return 0;}
		m>>=1;
	}
	return count;
}
	

static inline unsigned bit_of(uint64_t a, int i){
	return (a>>i)&1;
}

static uint64_t addmod(uint64_t a, uint64_t b, uint64_t m){
	uint64_t c=a+b;
	if(c>=a && c>=b){
		return mod(c, m);
	}
	else{
		c=mod(c+1, m);
		return addmod(c, umod, m);
	}
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m){
	uint64_t ind=pow2(m);
	if(ind!=0){
		return ((a+b)<<(65-ind))>>(65-ind);
	}
	umod=mod(umod, m);
	a=mod(a, m);
	//printf("a: %lu\n", a);
	b=mod(b, m);
	printf("%lu %lu %lu\n", a, b, m);
	uint64_t c=0;
	uint64_t tmp=b;
	for(int i=0; i<64; ++i){
		if(bit_of(a, i)==1){
			//printf("i:%d\n", i);
			c=addmod(c, tmp, m);
		}
		tmp=addmod(tmp, tmp, m);
	}
	return c;
}

int main(){
	uint64_t a, b, m;
	scanf("%lu%lu%lu", &a, &b, &m);
	//printf("a\n");
	printf("%lu\n", multimod(a, b, m));
	return 0;
}

/*
int main(){
	uint64_t a=2616528784434312442, b=12802892420729404147, m=10677790085944912985;
	//printf("%lu %lu %lu \n", a, b, m);
	printf("%lu\n", multimod(a, b, m));
	return 0;
}
*/
/*
int main(){
	FILE *fp=fopen("input", "r");
	assert(fp!=NULL);
	uint64_t a, b, m, ans;
	unsigned count=0;
	FILE *fpp=fopen("res", "w");
	for(int i=0; i<10000; ++i){
		assert(fscanf(fp, "%lu %lu %lu %lu", &a, &b, &m, &ans)!=EOF);
		printf("%lu %lu %lu %lu\n", a, b, m, ans);
		uint64_t c=multimod(a, b, m);
		if(ans!=c){
			++count;
			fprintf(fpp, "%d %lu %lu %lu %lu %lu\n", i, ans, c, a, b, m);
			printf("%d %lu %lu\n", i, ans, c);
		}
	}
	fclose(fpp);
	fclose(fp);
	printf("count: %u\n", count);
	return 0;
}
*/
