#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define u8 unsigned char 

const char* shps[4]={"Club","Diamond","Heart","Spade"};


typedef union{
    struct {
        unsigned shape: 2;
        unsigned num: 4;
        unsigned flag: 2;
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
        cnt=1;
        //printf("%d\n",crds[i].num);
        for(j=i;j<n;j++){
            if(crds[j].num==crds[j-1].num) continue;
            if(crds[j].num!=crds[j-1].num+1){
                i=j;    
                //printf(":%d\n",crds[i].num);
                break;
            }
            //printf("%d,%d\n",cnt,crds[j].num);
            cnt++;
            if(cnt>=5){
                sgt_cnt++;
                cnt=1;
                break; 
            }
        }
    }
    return sgt_cnt;
}



u8 fullh_t(int n, CardT *crds){
    u8 i,cnt,tmp_num,tri_cnt, dbl_cnt;
    cnt=1;tri_cnt=0;dbl_cnt=0;tmp_num=crds[0].num;
    for(i=1;i<n;i++ ){
        if(crds[i].num!=tmp_num){
            cnt=1;
            tmp_num=crds[i].num;
            continue;
        }
        cnt++;
        if(cnt==2){
            i++;
            if(crds[i].num==tmp_num){
                tri_cnt++;
            }else{
                dbl_cnt++;
                cnt=1;
                tmp_num=crds[i].num;
            }
        }
    }
    
    return dbl_cnt + (tri_cnt-1)*3*tri_cnt;
}



u8 fourk_t(int n, CardT *crds){
    u8 i,cnt,tmp_num,qua_cnt;
    cnt=1;qua_cnt=0;tmp_num=crds[0].num;
    for(i=1;i<n;i++ ){
       if(crds[i].num!=tmp_num){
            cnt=1;
            tmp_num=crds[i].num;
            continue;
       }
        cnt++;
        if(cnt==4){
            qua_cnt++;
        }
    }
    return qua_cnt; 
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
    CardT set4strt[13]={{0,1},{0,2},{1,3},{3,4},{1,5},{1,6},{2,6},{1,8},{1,9},{1,10},{1,11},{1,12},{0,12}};
    CardT set4fh[13]={{0,1},{0,1},{1,1},{3,2},{1,2},{1,6},{1,7},{1,8},{0,7},{3,7},{1,11},{1,8},{0,12}};
    CardT set4f[13]={{0,1},{2,1},{1,1},{3,1},{1,2},{1,6},{1,7},{1,8},{1,9},{3,12},{2,12},{1,12},{0,12}};
    
    u8 strt_rslt,fh_rslt,fourk_rslt,pr_rslt;
    u8 flag,sgt=1,flsh=1,trp_0,trp_1,fh_0,fh_1,fk_0,fk_1;
 
    CardT crds[13];
    draw_crds(13, crds);
    qsrt(0,12,crds);
    puts("------");
    for(int k=0;k<13;k++)show_crd(crds[k]);
     
    printf("full house:%d\n",fullh_t(13,crds));
    printf("four:%d\n",fourk_t(13,crds));
    printf("straight:%d\n",straight_t(13,crds));
    printf("pair:%d\n",pair_t(13,crds));
    puts("-------");
    printf("full house:%d\n",fullh_t(13,set4fh));
    printf("four:%d\n",fourk_t(13,set4f));
    printf("straight:%d\n",straight_t(13,set4strt));
    printf("pair:%d\n",pair_t(13,set4fh));



    return 0;
}
