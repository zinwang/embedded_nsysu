#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned char crds[5];
int crds_idx=-1;

char shpc[4]={'C','D','H','S'};


//a>b
int comp(unsigned char a, unsigned char b){
    int sa = a&3, sb = b&3;
    int na = a>>2, nb=b>>2;
    return na>nb?1:(na==nb?sa>sb:0);
}

/* int comp(unsigned char a, unsigned char b){
    return a>b;
}*/


void swap(unsigned char *a, unsigned char *b){
    unsigned char tmp=*a;
    *a=*b;
    *b=tmp;
}

int qpart(int lft, int rgt ){
    int i=lft,j=rgt,pivot=(i+j)/2;
    while(i<=j){
        while(comp(crds[pivot],crds[i])) i+=1;
        while(comp(crds[j],crds[pivot])) j-=1;
        if(i<=j){
            swap(&crds[i],&crds[j]);
            i+=1;
            j-=1;
        }
        
    }
    return i;
    
}


void qsort(int lft, int rgt){
    
    int p=qpart(lft,rgt);
    
    if(lft<p-1) qsort(lft,p-1);
    if(p<rgt) qsort(p,rgt);
}

void show_crd(unsigned char crd){
      
      printf("%c,%d\n",shpc[crd&3],crd>>2);

}







int main()
{
  int i,j,cnt,shp,pr_cnt;
  int flag,sgt=1,flsh=1,trp_0,trp_1,fh_0,fh_1,fk_0,fk_1;
  unsigned char tmp_crd,rn;
  while(crds_idx<4){
    flag=0;
    srandom(time(NULL));
    rn=random()%52;
    tmp_crd=((rn%13)<<2)|(rn/13);
    for(i=0;i<=crds_idx;i+=1){
      if(tmp_crd==crds[i]){
        flag=1;
        break;
      }
    }
    if(!flag){
      crds_idx+=1;
      crds[crds_idx]=tmp_crd;
      show_crd(tmp_crd);
    }
  }
  
  qsort(0,4);
  //for(int k=0;k<5;k++)printf("%d\n",crds[k]);
  //unsigned char c=4,d=21;
  //printf("%d",comp(c,d));
 
  // straight test
  cnt=int(crds[0]>>2);
  shp=crds[0]&3;
  for(j=1;j<5;j++){
  	cnt+=1;
	if(int(crds[i]>>2)!=cnt){
		sgt=0;
		break;
	}
	if(crds[i]&3!=shp){
		flsh=0;
	}
  }

  if(sgt){
	if(flsh) printf("Straight Flush!");
	else printf("Straight!");
  }
  

 // pair test
 pr_cnt=0;
 for(j=0;j<4;j++){
	if(int(crds[j]>>2) == int(crds[j+1]>>2))
		pr_cnt+=1;
 }
 if(pr_cnt){
	printf("Pairs exist! Total pairs number: %d",pr_cnt);
 }

 //fullhouse test
 trp_0 = (int(crds[0]>>2) == int(crds[1]>>2) && (int(crds[1]>>2) == int(crds[2]>>2)));
 trp_1 = (int(crds[2]>>2) == int(crds[3]>>2) && (int(crds[3]>>2) == int(crds[4]>>2)));
 fh_0 = (trp_0 && (int(crds[3]>>2) == int(crds[4]>>2))); 
 fh_1 = (trp_1 && (int(crds[0]>>2) == int(crds[1]>>2)));
 if(fh_0 || fh_1) printf("Full House!");
 
// Four of a kind test
 fk_0 = trp_0 && (crds[2]>>2 == crds[3]>>2);
 fk_1 = trp_1 && (crds[1]>>2 == crds[2]>>2);
 if(fk_0||fk_1) printf("Four of a kind!");


}
