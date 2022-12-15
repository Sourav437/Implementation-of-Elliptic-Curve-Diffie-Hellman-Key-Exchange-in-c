#include<stdio.h>
void change_base(unsigned char *a,long long int *A);
void addition( long long int *r, long long int *s, long long int *t,int n);
void mod_subtract(long long int *r, long long int *s, long long int *t,int n);
int Is_a_BiggerThan_b(long long int *a, long long int *b,int n);
void multi(long long int *r, long long int *s, long long int *t,int n);
void barret(long long int *r,long long int *R);
void square_multiply(long long int *x, long long int *a,long long int *result);
void ecc_addition(long long int *a_x,long long int *b_x, long long int *a_y, long long int *b_y,long long int *r_x,long long int *r_y);
void ecc_scalar_multiply(long long int *x, long long int *y, long long int *c, long long int *a, long long int *b);
void print_array(long long int *sourav,int n){
	for(int i=0;i<n;i++)
		printf("%lld\t",sourav[i]);
	printf("\n");
}
long long int p[10]={1073741823, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535},p_2[10]={1073741821, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535};
int main(){
	unsigned char r[32]={243, 212, 5, 39, 33, 146, 119, 117, 245, 85, 53, 42, 42, 143, 71, 204, 119, 202, 235, 101, 223, 162, 119, 122, 240, 127, 74, 4},s[32]={109, 56, 115, 155, 240, 27, 194, 45, 201, 191, 243, 86, 84, 232, 251, 142, 52, 202, 249, 186, 3, 54, 47, 177, 139, 203, 5};
	long long int a[9]={0},b[9]={0};
	//base change to 2^30
     	change_base(r,a);
       	change_base(s,b);
	int i;
       	long long int gx[9]={412664470, 310699287, 515062287, 14639179, 608236151, 865834382, 69500811, 880588875, 27415},gy[9]={935285237, 785973664, 857074924, 864867802, 262018603, 531442160, 670677230, 280543110, 20451};
       	long long int aG_x[9]={0},aG_y[9]={0};
       	//calculating aG
       	ecc_scalar_multiply(gx,gy,a,aG_x,aG_y);
       	printf("\naGx1\n");
       	print_array(aG_x,9);
       	printf("\naGy1\n");
       	print_array(aG_y,9);
       	printf("\n");
       	//calculating bG
       	long long int bG_x[9]={0},bG_y[9]={0};
     	ecc_scalar_multiply(gx,gy,b,bG_x,bG_y);
       	printf("\nbGx1\n");
       	print_array(bG_x,9);
       	printf("\nbGy1\n");
        print_array(bG_y,9);
       	printf("\n");
     	//calculate a*(bG)
     	printf("\na*(bG)");
     	long long int aBG_x[9]={0},aBG_y[9]={0};
     	ecc_scalar_multiply(bG_x,bG_y,a,aBG_x,aBG_y);
       	printf("\na*(bG)x1\n");
        print_array(aBG_x,9);
       	printf("\na*(bG)y1\n");
       	print_array(aBG_y,9);
       	printf("\n");
     	//calculate b*(aG)
     	printf("\nb*(aG)");
     	long long int bAG_x[9]={0},bAG_y[9]={0};
     	ecc_scalar_multiply(aG_x,aG_y,b,bAG_x,bAG_y);
       	printf("\nb*(aG)x1\n");
        print_array(bAG_x,9);
       	printf("\nb*(aG)y1\n");
       	print_array(bAG_y,9);
       	printf("\n");
     	if(Is_a_BiggerThan_b(bAG_x,aBG_x,9)==0 && Is_a_BiggerThan_b(bAG_y,aBG_y,9)==0)
     		printf("\nNow they have common key......\n");
     	else
     		printf("\nError in key exchange.........\n");    	
}
void ecc_scalar_multiply(long long int *x, long long int *y, long long int *c, long long int *a, long long int *b){
	long long int z1[9]={0},z2[9]={0},temp[9]={0},temp1[9]={0},sou1[9]={0},sou2[9]={0};
	int flag=0,i,j,B,k;
	for(i=0;i<9;i++){
		z1[i]=x[i];
		z2[i]=y[i];
	}
	for(i=8;i>=0;i--){
		for(j=29;j>=0;j--){
			B=(c[i]>>j) & 1;
			if(flag==1){
				ecc_addition(z1,z1,z2,z2,temp,temp1);
				for(k=0;k<9;k++){
					z1[k]=temp[k];
					z2[k]=temp1[k];
					
					temp[k]=0;
					temp1[k]=0;
				}
				if(B==1){
					ecc_addition(z1,x,z2,y,sou1,sou2);
					for(k=0;k<9;k++){
						z1[k]=sou1[k];
						z2[k]=sou2[k];
						
						sou1[k]=0;
						sou2[k]=0;
						}		
				}
				
			}
			if(B==1)
				flag=1;
		}
	}
	for(i=0;i<9;i++){
		a[i]=z1[i];
		b[i]=z2[i];
	}

}
void ecc_addition(long long int *a_x,long long int *b_x, long long int *a_y, long long int *b_y,long long int *r_x,long long int *r_y){
	int i;
	long long int p[10]={1073741823, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535},p_2[10]={1073741821, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535},p_3[10]={1073741820, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535},three[9]={3},y[9]={0},x[9]={0},x_inv[9]={0},two[9]={2},x_sq[9]={0};
	long long int lamda[18]={0},bar_lamda[9]={0},three_x[18]={0},three_x_barret[9]={0},num[10]={0},den[18]={0},den_bar[9]={0},sol[9]={0};
	long long int e1[18]={0};
	if((Is_a_BiggerThan_b(a_x,b_x,9)==0) && (Is_a_BiggerThan_b(a_y,b_y,9)==0)){
		multi(a_x,a_x,e1,9);
		barret(e1,x_sq);
		multi(x_sq,three,three_x,9);
		barret(three_x,three_x_barret);
		addition(three_x_barret,p_3,num,9);
		
		multi(two,a_y,den,9);
		barret(den,den_bar);
		square_multiply(den_bar,p_2,sol);
		multi(sol,num,lamda,9);	
	}
	else{
		if(Is_a_BiggerThan_b(b_y,a_y,9)==1)
			mod_subtract(b_y,a_y,y,9);
		if(Is_a_BiggerThan_b(b_y,a_y,9)==-1){
			long long int thik[9]={0};
			mod_subtract(a_y,b_y,thik,9);
			mod_subtract(p,thik,y,9);	
		}
		if(Is_a_BiggerThan_b(b_x,a_x,9)==1)
			mod_subtract(b_x,a_x,x,9);
		if(Is_a_BiggerThan_b(b_x,a_x,9)==-1){	
			long long int thik1[9]={0};
			mod_subtract(a_x,b_x,thik1,9);
			mod_subtract(p,thik1,x,9);
				
		}
		square_multiply(x,p_2,x_inv);
		multi(x_inv,y,lamda,9);			
	}	
	barret(lamda,bar_lamda);
	long long int temp[9]={0},temp1[10]={0},temp2[9]={0};
	square_multiply(bar_lamda,two,temp);
	if(Is_a_BiggerThan_b(temp,a_x,9)==1)
		mod_subtract(temp,a_x,temp1,9);
	else
		{
		mod_subtract(a_x,temp,temp2,9);
		mod_subtract(p,temp2,temp1,9);
		}
	long long int tis[9]={0};
	if(Is_a_BiggerThan_b(temp1,b_x,9)==1)
		mod_subtract(temp1,b_x,r_x,9);
	else
		{
		mod_subtract(b_x,temp1,tis,9);
		mod_subtract(p,tis,r_x,9);
		}	
	long long int tempy[9]={0},temp1y[20]={0},temp2y[9]={0},temp3y[9]={0};
	if(Is_a_BiggerThan_b(a_x,r_x,9)==1)
		mod_subtract(a_x,r_x,tempy,9);
	else{	
		long long int thik3[9]={0};
		mod_subtract(r_x,a_x,thik3,9);
		mod_subtract(p,thik3,tempy,9);	
	}	
	multi(tempy,bar_lamda,temp1y,9);
	barret(temp1y,temp2y);
	if(Is_a_BiggerThan_b(temp2y,a_y,9)==1)
		mod_subtract(temp2y,a_y,r_y,9);
	else{
		mod_subtract(a_y,temp2y,temp3y,9);
		mod_subtract(p,temp3y,r_y,9);
	}	
}
void square_multiply(long long int *x, long long int *a,long long int *result){
	long long int zid[9]={1},temp[18]={0},temp1[18]={0};
	for(int i=8;i>=0;i--){
		for(int j=29;j>=0;j--){
			for(int k=0;k<18;k++)
				temp[k]=0;
			multi(zid,zid,temp,9);
			for(int k=0;k<9;k++)
				zid[k]=0;
			barret(temp,zid);
			if((a[i]>>j) & 1){
				for(int k=0;k<18;k++)
					temp1[k]=0;
				multi(zid,x,temp1,9);
				for(int k=0;k<9;k++)
					zid[k]=0;
				barret(temp1,zid);
			}
		}
	}	
	for(int i=0;i<9;i++)
		result[i]=zid[i];
}

void barret(long long int *r,long long int *R){
	int i;
	//p=0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff ;; k=256//30 ;; B=2^30 
	long long int p[10]={1073741823, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535}; //calculated in sage
	long long int T[10]={805306368, 0, 0, 1073741820, 1073741807, 1073741759, 1073741567, 1073741823, 4095, 16384}; // T=B^2k/p calculated in sage
	long long int Q[10]={0},Q1[20]={0},Q2[10]={0},QP[20]={0};
	//Q=[x/B^k-1]=[r/2^240]
	for(i=0;i<10;i++)
		Q[i]=r[8+i];
	multi(Q,T,Q1,10);
	//Q2 <- Q1/B^k+1=Q/2^300
	for(i=0;i<10;i++)
		Q2[i]=Q1[10+i];
	multi(Q2,p,QP,10);
	long long int r_dash[10]={0},QP_dash[10]={0};
	for(i=0;i<10;i++){
		r_dash[i]=r[i]; //r mod2^300
		QP_dash[i]=QP[i]; //QP mod2^300	
	}
	if(Is_a_BiggerThan_b(r_dash,QP_dash,10)==1)
     		mod_subtract(r_dash,QP_dash,R,10);
     	if(Is_a_BiggerThan_b(r_dash,QP_dash,10)==-1){
     		long long int thikthik[10]={0};
     	    	mod_subtract(QP_dash,r_dash,thikthik,10);
     	    	mod_subtract(p,thikthik,R,10);
     	    	}
	while(1==Is_a_BiggerThan_b(R,p,10)){
		long long int te[10]={0};
		mod_subtract(R,p,te,10);
		for(i=0;i<10;i++)
			R[i]=te[i];
		}	
}

void addition( long long int *r, long long int *s, long long int *t,int n){

	int i;
	long long int carry=0;
	for(i=0;i<n;i++){
		t[i]=r[i]+s[i]+carry;
		carry=(t[i]>>30);
		t[i]=t[i] & 0x3fffffff;
		/*if(t[i] >= (1<<30)){
			t[i+1] = t[i+1] + 1;
			t[i]   = t[i] & 0b111111111111111111111111111111;
		} */
	}
	t[9]=carry;
}

int Is_a_BiggerThan_b(long long int *a, long long int *b,int n){
	int i,flag=0;
        for(i=n-1;i>=0;i--){
       		if(a[i] > b[i]){
       			flag=1;
     			break;       		
       		}
		if(a[i] < b[i]){
       			flag=-1;
     			break;       		
       		}
	}	
	return flag;	
}

void mod_subtract(long long int *r_dash, long long int *s, long long int *t,int n){
	int i;
	long long int r[20]={0};
	for(i=0;i<n;i++)
		r[i]=r_dash[i];
	for(i=0;i<n;i++){
		t[i]=r[i]-s[i];
		if((t[i]>>63) & 1){//checking the sign bit
			t[i]+= 1<<30;
			r[i+1]-=1;	
		}
	}
	
}

void multi(long long int *r, long long int *s, long long int *t,int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			t[i+j]+=r[i]*s[j];
			t[i+j+1]+= (t[i+j]>>30);
			t[i+j]=t[i+j] & 0x3fffffff;
		}
	}
}

void change_base(unsigned char *a,long long int *A){
	
A[0] = (long long int)a[0] | ((long long int)a[1] << 8) | (long long int)a[2]<<16 | ((long long int)a[3] & 0X3F)<<24;
A[1] = ((long long int)a[3] >> 6)  | (long long int)a[4]<<2 | (long long int)a[5]<<10 | (long long int)a[6]<<18 | ((long long int)a[7] & 0XF)<<26;
A[2] = ((long long int) a[7] >>4) | (long long int) a[8] <<4 | (long long int) a[9] << 12 | (long long int) a[10] <<20 | ((long long int)a[11]  & 0x3 )<<28 ;
A[3] = ( (long long int) a[11])>>2 | ((long long int) a[12] )<<6 | ((long long int) a[13] )<<14 | ((long long int) a[14] )<<22; 

A[4] = (long long int)a[15] | ((long long int)a[16] << 8) | (long long int)a[17]<<16 | ((long long int)a[18] & 0X3F)<<24;
A[5] = ((long long int)a[18] >> 6)  | (long long int)a[19]<<2 | (long long int)a[20]<<10 | (long long int)a[21]<<18 | ((long long int)a[22] & 0XF)<<26;
A[6] = ((long long int) a[22] >>4) | (long long int) a[23] <<4 | (long long int) a[24] << 12 | (long long int) a[25] <<20 | ((long long int)a[26]  & 0x3 )<<28 ;
A[7] = ( (long long int) a[26])>>2 | ((long long int) a[27] )<<6 | ((long long int) a[28] )<<14 | ((long long int) a[29] )<<22; 

A[8] = (long long int) a[30] | (long long int) a[31] << 8 ;

}
