#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct player{
  char name[20];
  int sex;
  int dif;  //Difficulty  難易度
  int actcon; //Acting Configuration  演技構成
  int stab; //Stability 操作安定度
  int nov;  //Novelty 新規性
  int ded; //Deduction 減点
}P;

int input(P *); //データを入力する
int output(P *);  //画面に出力
//int filewrite();  //ファイルに出力
//int sort(); //順位ごとにソートし名前を画面出力

int main(){
  int num,i;
  P *pp;

  printf("player number >");
  do{
    scanf("%d",&num); //選手人数
  }while(num<0);
  pp=(P*)malloc(sizeof(P)*num);

  for(i=0;i<num;i++){
    input(pp+i);
  }

  for(i=0;i<num;i++){
    output(pp+i);
  }

  //ファイル出力する関数
  //順位をソートする関数

  return 0;
}


int input(P *pp){
  int i;
  printf("player name>");
  scanf("%s",pp->name[20]);
  for(i=0;i<6;i++){
    switch(i){
      case 0:
        printf("player's sex (male:0 or female:1)>");
        do{
          scanf(" %d",pp->sex);
        }while(((pp->sex)<0)||(2<(pp->sex)));
        break;
      case 1: //難易度
        printf("Difficulty point (0-40)>");
        do{
          scanf(" %d",pp->dif);
        }while(((pp->dif)<0)||(40<(pp->dif)));
        break;
      case 2: //演技構成
        printf("Acting Configuration point (0-25)>");
        do{
          scanf(" %d",pp->actcon);
        }while(((pp->actcon)<0)||(25<(pp->actcon)));
        break;
      case 3: //安定
        printf("Stability point (0-20)>");
        do{
          scanf(" %d",pp->stab);
        }while(((pp->stab)<0)||(20<(pp->stab)));
        break;
      case 4: //新規性
        printf("Novelty point (0-15)>");
        do{
          scanf(" %d",pp->nov);
        }while(((pp->nov)<0)||(15<(pp->nov)));
        break;
      case 5: //減点
        printf("Deduction point>");
        do{
          scanf(" %d",pp->ded);
        }while((pp->ded)<0);
        break;
    }; //if文で5以上をはじいているのでdefault無し
  }
  return 0;
}


int output(P *pp){
  int total;
  total=(pp->dif)+(pp->actcon)+(pp->stab)+(pp->nov)-(pp->ded);
  printf("player name> %s\n",pp->name[20]);
  if((pp->sex)==0){
    printf("player's sex> male\n");
  }else{
    printf("player's sex> female\n");
  }
  printf("Difficulty point (0-40)> %d\n",pp->dif);
  printf("Acting Configuration point (0-25)> %d\n",pp->actcon);
  printf("Stability point (0-20)> %d\n",pp->stab);
  printf("Novelty point (0-15)> %d\n",pp->nov);
  printf("Deduction point> %d\n",pp->ded);
  printf("Total point> %d\n",total);

}
