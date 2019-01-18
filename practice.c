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
  struct player *p;
}P;

int sw(int ,P *);
int input(P *); //データを入力する
int output(P *);  //画面に出力
int sort(int ,P *); //順位振り分け
int filewrite(P *);  //ファイルに出力
int ranksort(int ,P *); //順位を画面表示する形にソート
int sortout(P *); //順位を画面出力
int freedata(P *);


int main(){
  int num,i;
  P *first,*next;
  system("cls");
  printf("###     Data input application.     ###\n");
  printf("### You must put \'f\' with last data.###\n");

  first=(P *)malloc(sizeof(P));
  num=input(first);

  for(i=0;i<num;i++){
    if(i==0){
      output(first);
    }else{
      next=first->p;
      free(first);
      first=next;
      output(first);
    }
  }

  sort(num,first);

  for(i=0;i<num;i++){
    if(i==0){
      filewrite(first);
    }else{
      next=first->p;
      free(first);
      first=next;
      filewrite(first);
    }
  }

  ranksort(num,first);

  for(i=0;i<num;i++){
    if(i==0){
      sortout(first);
    }else{
      next=first->p;
      free(first);
      first=next;
      sortout(first);
    }
  }

  printf("Data number = %d\n\n",num);
  freedata(first);

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


int input(P *now){
  int i,num=0;
  char c;
    P *next;

  while(1){
    printf("\nnunber of player> %d\n",++num);
    (now->number)=num;
    (now->rank)=num;
    printf("player name>");
    scanf(" %s",now->name);
    for(i=0;i<6;i++){
      sw(i,now);
    }
    printf("fin ? >");
    scanf(" %c",&c);
    if(c=='f'){
      now->p = NULL;
      break;
    }else{
      next=(P *)malloc(sizeof(P));  //データ入力のためのメモリ確保
      now->p=next;  //次のデータのアドレスを設定
      now=next; //次のデータの入力じゅんび
    }
  }
  return num;
}


int output(P *pp){
  int total;
  (pp->total)=(pp->dif)+(pp->actcon)+(pp->stab)+(pp->nov)-(pp->ded);
  printf("\n\nplayer nunber> %d\n",pp->number);
  printf("player name> %s\n",pp->name);
  if((pp->sex)==0){
    strcpy((pp->sexs),"male");
    printf("player's sex> %s\n",pp->sexs);
  }else{
    strcpy((pp->sexs),"female");
    printf("player's sex> female\n",pp->sexs);
  }
  printf("Difficulty point (0-40)> %d\n",pp->dif);
  printf("Acting Configuration point (0-25)> %d\n",pp->actcon);
  printf("Stability point (0-20)> %d\n",pp->stab);
  printf("Novelty point (0-15)> %d\n",pp->nov);
  printf("Deduction point> %d\n",pp->ded);
  printf("Total point> %d\n\n",pp->total);

  return 0;
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


int filewrite(P *pp){
  FILE *datafp;
  datafp=fopen("playerdata.csv","a");
  if(datafp==NULL){
        printf("\n");
        return -1;
    }else{
        printf("\nFile open.\n");
    }

    fprintf(datafp,"%d,",pp->number);
    fprintf(datafp,"%s,",pp->name);
    fprintf(datafp,"%s,",pp->sexs);
    fprintf(datafp,"%d,",pp->dif);
    fprintf(datafp,"%d,",pp->actcon);
    fprintf(datafp,"%d,",pp->stab);
    fprintf(datafp,"%d,",pp->nov);
    fprintf(datafp,"%d,",pp->ded);
    fprintf(datafp,"%d,",pp->total);
    fprintf(datafp,"%d,",pp->rank);
    fprintf(datafp,"\n");

    fclose(datafp);
    printf("File close.\n");
    return 0;
}


int ranksort(int num,P *pp){
  int i,j,tmp,tmpr;
  char tmps[20];
  for (i=0; i<num; ++i) {
    for (j=i+1; j<num; ++j) {
      if (((pp+i)->rank)>((pp+j)->rank)) {
        tmpr = ((pp+i)->rank);
        ((pp+i)->rank)=((pp+j)->rank);
        ((pp+j)->rank)= tmpr;

        tmp = ((pp+i)->number);
        ((pp+i)->number)=((pp+j)->number);
        ((pp+j)->number)= tmp;

        strcpy(tmps,((pp+i)->name));
        strcpy(((pp+i)->name),((pp+j)->name));
        strcpy(((pp+j)->name),tmps);
      }
    }
  }
  return 0;
}


int sortout(P *pp){
  printf("player rank:%d ",pp->rank);
  printf("nunber:%d ",pp->number);
  printf("name:%s\n",pp->name);
  return 0;
}

int freedata(P *now){
    int num=0;
    P *next;
    while(1){
        if(now->p != NULL){
            next=now->p;
            free(now);
            now=next;
        }else{
            printf("Finish.\n");
            break;
        }
    }
    return 0;
}
