#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct player{
  int number;
  char name[20];
  int sex;
  char sexs[10];
  int dif;  //Difficulty  難易度
  int actcon; //Acting Configuration  演技構成
  int stab; //Stability 操作安定度
  int nov;  //Novelty 新規性
  int ded; //Deduction 減点
  int total;
  struct player *next;
}P;

int sw(int ,P *);
int input(P *); //データを入力する
int output(P *,P *);  //画面に出力
int sort(P *,P *,int); //順位振り分け
int freedata(P *);

int main(){
  int num,i;
  P start;  //リストの先頭の構造体変数
  P *work;  //作業用のポインタ

  printf("\n###     Data input application.     ###\n");
  printf("### You must put \'f\' with last data.###\n");

  work = &start;
  work->next = NULL;

  num=input(work);
  sort(&start,work,num);
  output(&start,work);
  printf("\nData number = %d\n",num);
  freedata(work);

  return 0;
}

int sw(int i,P *pp){
  switch(i){
    case 0:
      do{
        printf("player's sex (male:0 or female:1)>");
        scanf(" %d",&pp->sex);
      }while(((pp->sex)<0)||(1<(pp->sex)));
      break;
    case 1: //難易度
      do{
        printf("Difficulty point (0-40)>");
        scanf(" %d",&pp->dif);
      }while(((pp->dif)<0)||(40<(pp->dif)));
      break;
    case 2: //演技構成
      do{
        printf("Acting Configuration point (0-25)>");
        scanf(" %d",&pp->actcon);
      }while(((pp->actcon)<0)||(25<(pp->actcon)));
      break;
    case 3: //安定
      do{
        printf("Stability point (0-20)>");
        scanf(" %d",&pp->stab);
      }while(((pp->stab)<0)||(20<(pp->stab)));
      break;
    case 4: //新規性
      do{
        printf("Novelty point (0-15)>");
        scanf(" %d",&pp->nov);
      }while(((pp->nov)<0)||(15<(pp->nov)));
      break;
    case 5: //減点
      do{
        printf("Deduction point>");
        scanf(" %d",&pp->ded);
      }while((pp->ded)<0);
      break;
    case 6:
      (pp->total)=(pp->dif)+(pp->actcon)+(pp->stab)+(pp->nov)-(pp->ded);
      printf("Total point>%d\n",pp->total);
      break;
    default:
      return -1;
  };
  return 0;
}

int input(P *work){
  int i,num=0;
  char c;
  P *new,*new1;

  new=(P *)malloc(sizeof(P));
  work->next=new;
  new->next = NULL;

  while(1){
    printf("\nnumber of player> %d\n",++num);
    (new->number)=num;
    printf("player name>");
    scanf(" %s",new->name);
    for(i=0;i<7;i++){
      sw(i,new);
    }

    printf("fin ? >");
    scanf(" %c",&c);
    if(c=='f'){
      break;
    }

    new1=(P *)malloc(sizeof(P));
    if(new1 == NULL){
      printf("Nothing Memory.\n");
      return -1;
    }

    new->next=new1;
    new = new1;
  }

  return num;
}

int sort(P *start,P *work,int num){
  P *tmp,*tmp2,*now,*next;
  int i;

  for(i=0;i<num+1;i++){
    work = start;
    now = work->next;
    next=now->next;
    for(;next != NULL;){
      if(now->total < next->total){
        tmp=next;
        now->next=tmp->next;
        tmp2=work->next;
        work->next=tmp;
        tmp->next=tmp2;
      }
      work=work->next;
      now=work->next;
      next=now->next;
    }
  }
  return 0;
}

int output(P *start,P *work){
  int rank;
  rank=1;
  work=start->next;
  printf("\n\n###  Player Data Output  ###\n");
  while(work!=NULL){
    printf("\nplayer rank> %d\n",rank);
    printf("player number> %d\n",work->number);
    printf("player name> %s\n",work->name);
    if((work->sex)==0){
      strcpy((work->sexs),"male");
      printf("player's sex> %s\n",work->sexs);
    }else{
      strcpy((work->sexs),"female");
      printf("player's sex> female\n",work->sexs);
    }
    printf("Difficulty point (0-40)> %d\n",work->dif);
    printf("Acting Configuration point (0-25)> %d\n",work->actcon);
    printf("Stability point (0-20)> %d\n",work->stab);
    printf("Novelty point (0-15)> %d\n",work->nov);
    printf("Deduction point> %d\n",work->ded);
    printf("Total point> %d\n",work->total);

    FILE *datafp;
    datafp=fopen("playerdata.csv","a");
    if(datafp==NULL){
      printf("\n");
      return -1;
    }else{
      printf("###  File open.  ###\n");
    }
    fprintf(datafp,"%d,",work->number);
    fprintf(datafp,"%s,",work->name);
    fprintf(datafp,"%s,",work->sexs);
    fprintf(datafp,"%d,",work->dif);
    fprintf(datafp,"%d,",work->actcon);
    fprintf(datafp,"%d,",work->stab);
    fprintf(datafp,"%d,",work->nov);
    fprintf(datafp,"%d,",work->ded);
    fprintf(datafp,"%d,",work->total);
    fprintf(datafp,"%d,",rank);
    fprintf(datafp,"\n");
    fclose(datafp);
    printf("###  File close.  ###\n");

    rank++;
    work=work->next;
  }
  return 0;
}

int freedata(P *work){
  int num=0;
  P *work2;
  while(work!=NULL){
    work2 = work->next;
    free(work);
    work = work2;
  }
  printf("###  Free Memory.  ###\n");
  return 0;
}
