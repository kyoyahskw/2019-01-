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
  int rank; //順位
  struct player *next; //次のデータへのポインタ
}P;

int sw(int ,P *);
int input(P *); //データを入力する
int output(P ,P *);  //画面に出力
int sort(int ,P *); //順位振り分け
int filewrite(P *);  //ファイルに出力
int ranksort(int ,P *); //順位を画面表示する形にソート
int sortout(P *); //順位を画面出力
int freedata(P *);


int main(){
  int num,i;
  P start; //リストの先頭の構造体変数
  P *work; //作業用のポインタ

  printf("###     Data input application.     ###\n");
  printf("### You must put \'f\' with last data.###\n");

  work = &start;
  work->next = NULL;

  num=input(work);

  output(start,work);

  printf("Data number = %d\n\n",num);

  freedata(work);

  return 0;
}


int sw(int i,P *pp){
  switch(i){
    case 0:
      printf("player's sex (male:0 or female:1)>");
      do{
        scanf(" %d",&pp->sex);
      }while(((pp->sex)<0)||(1<(pp->sex)));
      break;
    case 1: //難易度
      printf("Difficulty point (0-40)>");
      do{
        scanf(" %d",&pp->dif);
      }while(((pp->dif)<0)||(40<(pp->dif)));
      break;
    case 2: //演技構成
      printf("Acting Configuration point (0-25)>");
      do{
        scanf(" %d",&pp->actcon);
      }while(((pp->actcon)<0)||(25<(pp->actcon)));
      break;
    case 3: //安定
      printf("Stability point (0-20)>");
      do{
        scanf(" %d",&pp->stab);
      }while(((pp->stab)<0)||(20<(pp->stab)));
      break;
    case 4: //新規性
      printf("Novelty point (0-15)>");
      do{
        scanf(" %d",&pp->nov);
      }while(((pp->nov)<0)||(15<(pp->nov)));
      break;
    case 5: //減点
      printf("Deduction point>");
      do{
        scanf(" %d",&pp->ded);
      }while((pp->ded)<0);
      break;
    default:
      return -1;
  };
  return 0;
}


int input(P *work){
  int i,num=0;
  char c;
  P *new;

  while(1){
    new=(P *)malloc(sizeof(P));
    if(new == NULL){
      printf("Nothing Memory.\n");
      exit(1);
    }
    printf("\nnumber of player> %d\n",++num);
    (new->number)=num;
    (new->rank)=num;
    printf("player name>");
    scanf(" %s",new->name);
    for(i=0;i<6;i++){
      sw(i,new);
    }

    printf("fin ? >");
    scanf(" %c",&c);
    if(c=='f'){
      work->next = new;
      new->next = NULL;
      break;
    }else{
      work->next = new;
      new->next = NULL;
      work = new;
    }
  }
  return num;
}


int sort(int num,P *pp){
  int i,j,tmp;
  for(i=0;i<num;++i){
    for(j=i+1;j<num;++j){
      if(((pp+i)->total)<((pp+j)->total)){
        tmp=((pp+i)->rank);
        ((pp+i)->rank)=((pp+j)->rank);
        ((pp+j)->rank)=tmp;
      }
    }
  }
  return 0;
}


int output(P start,P *work){
  work=start.next;
  while(work!=NULL){
    int total;
    (work->total)=(work->dif)+(work->actcon)+(work->stab)+(work->nov)-(work->ded);
    printf("\n\nplayer nunber> %d\n",work->number);
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
    printf("Rank> %d\n\n",work->rank);

    work=work->next;
  }
  return 0;
}





int freedata(P *work){
  int num=0;
  P *work2;
  while(work!=NULL){
    work2=work->next;
    free(work);
    work=work2;
  }
  printf("Free Memory.\n");
  return 0;
}
