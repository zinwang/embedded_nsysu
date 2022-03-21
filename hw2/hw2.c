#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define u8 unsigned char 

const char* shps[4]={"Club","Diamond","Heart","Spade"};


typedef union{
    struct {
        unsigned shape: 2;
        unsigned num: 6;
    };
    u8 Card;
}CardT;



//a>b
u8 comp(CardT a, CardT b){
    //return a.num>b.num?1:(a.num==b.num?a.shape>b.shape:0);
    return a.Card>b.Card;
}



void swap(CardT *a, CardT *b){
    CardT tmp=*a;
    *a=*b;
    *b=tmp;
}

u8 qpart(u8 lft, u8 rgt, CardT *crds){
    u8 i=lft,j=rgt;
    u8 pivot=(i+j)/2;
    while(i<=j&&i<52&&j<52){   //i,j<52 ==> limit 0<=i,j<52 , where i,j are unsigned values
        while(comp(crds[pivot],crds[i])) i+=1;
        while(comp(crds[j],crds[pivot])) j-=1;
        
        //printf("%u,%u\n",i,j);
        if(i<=j&&i<52&&j<52){
            swap(crds+i,crds+j);
            i+=1;
            j-=1;
        }
        
    }
    return i;
    
}


void qsrt(u8 lft, u8 rgt, CardT *crds){
    u8 p=qpart(lft,rgt,crds);
    
    if(lft<p-1) qsrt(lft,p-1,crds);
    if(p<rgt) qsrt(p,rgt,crds);
}

void show_crd(CardT crd){     
    printf("%s,%d\n",shps[crd.shape],crd.num);
    return;
}

void draw_crds(u8 n, CardT *crds){
  u8 flag, i;
  char crds_idx=0;  
  u8 rn;
  CardT tmp_crd;

  while(crds_idx<n){
    flag=0;
    rn=random()%52;
    tmp_crd.shape=rn/13;
    tmp_crd.num=rn>>2;
    for(i=0;i<crds_idx;i+=1){
       if(tmp_crd.Card==crds[i].Card){
        flag=1;
        break;
      }
    }
    //printf("%d,%d\n",rn,crds_idx);
    //printf("%d",flag);
    if(!flag){
      crds[crds_idx]=tmp_crd;
      crds_idx+=1;
      show_crd(tmp_crd);
    }
  }   

}

//n:total card nums
u8 straight_t(u8 n,CardT *crds){
    u8 i,j,cnt,sgt_cnt;
    cnt=1;
    sgt_cnt=0;
    for(i=1;i<n;i++){
        if(crds[i].num==crds[i-1].num+1){
            //printf("%d,%d\n",cnt,crds[i].num);
            cnt++;
        }
        if(cnt==5){
            sgt_cnt++;
            cnt=1;
            i++;
        }
    }
    return sgt_cnt;
}



u8 fullh_t(int n, CardT *crds){
    u8 trp_0,trp_1,fh_0,fh_1;
    trp_0 = (crds[0].num == crds[1].num && crds[1].num == crds[2].num);
    trp_1 = (crds[2].num == crds[3].num && crds[3].num == crds[4].num);
    fh_0 = (trp_0 && crds[3].num == crds[4].num); 
    fh_1 = (trp_1 && crds[0].num == crds[1].num);
    return fh_0 || fh_1; 
  
}

u8 fourk_t(int n, CardT *crds){
    u8 fk_0,fk_1,trp_0,trp_1;
    trp_0 = (crds[0].num == crds[1].num && crds[1].num == crds[2].num);
    trp_1 = (crds[2].num == crds[3].num && crds[3].num == crds[4].num);
    fk_0 = trp_0 && (crds[2].num == crds[3].num);
    fk_1 = trp_1 && (crds[1].num == crds[2].num);
    return fk_0||fk_1;
}

u8 pair_t(int n, CardT *crds){
    u8 pr_cnt,i;
    pr_cnt=0;
    for(i=0;i<4;i++){
        if(crds[i].num == crds[i+1].num)
            pr_cnt+=1;
    }
    return pr_cnt;

}







int main()
{
    srandom(time(NULL));
    CardT set4strt[5]={{0,1},{0,2},{1,3},{3,4},{1,5}};
    CardT set4fh[5]={{0,1},{0,1},{1,1},{3,2},{1,2}};
    CardT set4f[5]={{0,1},{0,1},{1,1},{3,1},{1,2}};
    
    u8 strt_rslt,fh_rslt,fourk_rslt,pr_rslt;
    u8 flag,sgt=1,flsh=1,trp_0,trp_1,fh_0,fh_1,fk_0,fk_1;
 
    CardT crds[5];
    draw_crds(5, crds);
  
    qsrt(0,4,crds);
    //for(int k=0;k<5;k++)show_crd(crds[k]);
  
    printf("full house:%d\n",fullh_t(5,set4fh));
    printf("four:%d\n",fourk_t(5,set4f));
    

    // straight test
    printf("straight:%d\n",straight_t(5,set4strt));
  
    strt_rslt=straight_t(5,crds);
    if(strt_rslt){
        printf("There are %d set of Straights!",strt_rslt);
    }

    //fullhouse test
    fh_rslt=fullh_t(5,crds);
    if(fh_rslt)printf("Full House!");

    // Four of a kind test
    fourk_rslt=fourk_t(5,crds);
    if(fourk_rslt) printf("Four of a kind!");
   
    // pair test

    //CardT set4pr[5]={{1,5},{2,9},{3,9},{2,7},{1,5}};
    //printf("t%d\n",pair_t(5,set4pr));
    pr_rslt=pair_t(5,crds);
    if(pr_rslt){
        printf("Pairs exist! Total pairs number: %d",pr_rslt);
    }


    return 0;
}
