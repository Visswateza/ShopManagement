#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

char Name[51][13];
int Cost[51],StA[51],SoD[51];
int SSAm=0;

void heading()
{
	clrscr();
	printf("<<<<<<<<<<<<<<<<================================================>>>>>>>>>>>>>>>>");
	printf("<<<<<<<<		       T H E  S H O P                           >>>>>>>>");
	printf("<<<<<<<<<<<<<<<<================================================>>>>>>>>>>>>>>>>");
	printf("\n");
}

void main()
{
	time_t now = time(NULL);

	//Strat of Main menu
	int a,i,O,N=50,S=0;

	FILE *PNAME,*PCOST,*PStA,*NOP,*RSWS;

	PNAME=fopen("P_NAME.txt","r");
	for(i=0;i<51;i++)
	{
		fscanf(PNAME,"%s\n",Name[i]);
	}
	fclose(PNAME);

	PCOST=fopen("P_COST.txt","r");
	for(i=0;i<51;i++)
	{
		fscanf(PCOST,"%d\n",&Cost[i]);
	}
	fclose(PCOST);

	PStA=fopen("P_StA.txt","r");
	for(i=0;i<51;i++)
	{
		fscanf(PStA,"%d\n",&StA[i]);
	}
	fclose(PStA);

	NOP=fopen("TS_NOP.txt","r");
	fscanf(NOP,"%d\n%d\n",&S,&N);
	fclose(NOP);
	S++;

	clrscr();

	Main_Menu :

	heading();
	printf("\n\n                                                Current Session is %d.\n\n",S);
	printf("\n		1. Start Sale \n");
	printf("					2. Update Product Details \n");
	printf("		3. Session Statistics \n");
	printf("                                        4. Update stock \n");
	printf("		5. Settings \n");
	printf("					0. Exit \n\n\n");
	printf("	Enter your option : ");
	scanf("%d",&O);

	//Strat of Menu Functions
	switch(O)
	{
		case 0:
			NOP=fopen("TS_NOP.txt","w");
			fprintf(NOP,"%d\n%d\n",S,N);
			fclose(NOP);

			RSWS=fopen("SES_W_RE.txt","a");
			//fprintf(RSWS,"Date & Time         : %s \n",ctime(&now));
			fprintf(RSWS,"Session ID          : %d \n",S);
			fprintf(RSWS,"Date & Time         : %s",ctime(&now));
			fprintf(RSWS,"Session Total Sale  : %d Rs\\\- \n\n",SSAm);
			fclose(RSWS);

			exit(1);

		case 1: //Sale Place
			Sale :
			heading();
			printf("				   S A L E                                      ");
			printf("				~~~~~~~~~~~~~					");
			printf("                                                Current Session is %d.\n",S);
			printf("					     	Press 0 to go back. \n\n");

			//Print_ProDet();
			for(a=1;a<=N;a++)
			{
				if(StA[a]==0)
					printf("%.2d.%.10s [SNA]  ",a,Name[a]);
				else
					printf("%.2d.%.10s [%3d]  ",a,Name[a],Cost[a]);
				if(a%4==0)
					printf("\n");
			}
			printf("\n\n");

			printf("	Product Sold : ");
			scanf("%d",&i);
			if(i==0)
			{
				//FILE *PStA;
				PStA=fopen("P_StA.txt","w");
				for(i=0;i<51;i++)
				{
					fprintf(PStA,"%d\n",StA[i]);
				}
				fclose(PStA);

				goto Main_Menu;
			}
			if(StA[i]==0)
			{
				printf("		Stock not available");
				getch();
				goto Sale;
			}

			if( i>=1 && i<=N )
			{
				//sale(i);
				StA[i]--;
				SoD[i]++;
				SSAm=SSAm+Cost[i];
				goto Sale;
			}
			else
			{
				printf("\n\tPlease enter careflly");
				getch();
				goto Sale;
			}
			//break;

		case 2: //Sale Place
			UpPro :
			heading();
			printf("				   Details                                      ");
			printf("				~~~~~~~~~~~~~					");
			printf("                                                Current Session is %d.\n",S);
			printf("					     	Press 0 to go back. \n\n");

			//Print_ProDet();
			for(a=1;a<=N;a++)
			{
				printf("%.2d.%.10s [%3d]  ",a,Name[a],Cost[a]);
				if(a%4==0)
					printf("\n");
			}
			printf("\n\n");

			printf("	Enter product ID to make changes : ");
			scanf("%d",&i);
			if(i==0)
			{
				FILE *PNAME;
				PNAME=fopen("P_NAME.txt","w");
				for(i=0;i<=N;i++)
				{
					fprintf(PNAME,"%s\n",Name[i]);
				}
				fclose(PNAME);

				FILE *PCOST;
				PCOST=fopen("P_COST.txt","w");
				for(i=0;i<51;i++)
				{
					fprintf(PCOST,"%d\n",Cost[i]);
				}
				fclose(PCOST);

				goto Main_Menu;
			}
			if( i>=1 && i<=N )
			{
				float Cos;
				heading();
				printf("\n\n");
				printf("		Name	: %s\n",Name[i]);
				printf("		Cost	: %d\n",Cost[i]);
				printf("\n		Enter new details	\n");
				printf("\n		Name	: ");
				scanf("%s",Name[i]);
				printf("		Cost	: ");
				scanf("%f",&Cos);
				printf("\n\n	New Details\n");
				printf("		Name	: %s\n",Name[i]);
				printf("		Cost	: %d\n",Cost[i]);
				Cost[i]=Cos;
				goto UpPro;
			}
			else
			{
				printf("\n\tPlease enter careflly");
				getch();
				goto UpPro;
			}
			//break;


		case 3: //Session Statistics
			heading();
			printf("			        SESSION SALE                                    ");
			printf("			       ~~~~~~~~~~~~~~					");
			printf("                                                Current Session is %d.\n",S);
			printf("					     	Press any key to go back.\n\n");

			for(a=1;a<=N;a++)
			{
				printf("%.2d.%.10s [%3d]  ",a,Name[a],SoD[a]);
				if(a%4==0)
					printf("\n");
			}
			printf("\n\n");

			printf("\tSession total sale is %d Rs/-",SSAm);
			getch();
			goto Main_Menu;

		case 4: // Update Stock
			UpStc :
			heading();
			printf("				UPDATE STOCK                                    ");
			printf("			       ~~~~~~~~~~~~~~                                   ");
			printf("                                                Current Session is %d.\n",S);
			printf("					     	Press 0 to go back. \n\n");
			for(a=1;a<=N;a++)
			{
				if(StA[a]==0)
					printf("%.2d.%.6s [SNA]\t",a,Name[a]);
				else
					printf("%.2d.%.6s [%d]\t",a,Name[a],StA[a]);
				if(a%4==0)
					printf("\n");
			}
			printf("\n\n");
			printf("	Enter product ID to make changes : ");
			scanf("%d",&i);
			if(i==0)
			{
				FILE *PStA;
				PStA=fopen("P_StA.txt","w");
				for(i=0;i<51;i++)
				{
					fprintf(PStA,"%d\n",StA[i]);
				}
				fclose(PStA);

				goto Main_Menu;
			}
			if( i>=1 && i<=N )
			{
				heading();
				float j;
			      //	StA[i]=0;
				printf("\n\n");
				printf("		Name			: %s\n",Name[i]);
				printf("		Stock Available		: %d\n",StA[i]);
				printf("\n		Enter new details	\n");
				//printf("\n		Name			: ");
				//scanf("%s",P[i].Name);
				printf("		Add Stock  Qt		: ");
				scanf("%f",&j);
				//printf("\n\n\"%d\n\n",j);
				//getch();
				StA[i]+=j;
				printf("		New Stock Available	: %d", StA[i]);
				getch();
				goto UpStc;
			}
			else
			{
				printf("\n\tPlease enter careflly");
				getch();
				goto UpStc;
			}
			//break;

			//printf("\n\n\tThe Product\n\n");

		case 5: //SETTING_S
			Settings :
			heading();
			printf("				  SETTING_S                                     ");
			printf("				~~~~~~~~~~~~~					");
			printf("                                                Current Session is %d.\n",S);
			//printf("					     	Press 0 to goto Main Menu \n\n");
			printf("\n\n");
			printf("\tYou are currently managing %d products.\n\n",N);
			printf("\tPress 1 to change No.Of Products\n");
			printf("\tPress 0 to continue.\n");
			scanf("%d",&i);
			if(i==1)
			{
				printf("\n\n\tEnter new No.of Products : ");
				scanf("%d",&N);
				printf("\tNew No.of Products is %d.",N);
				getch();
				goto Settings;
			}
			if(i==0)
				goto Main_Menu;
			printf("\n\n\t\tPlease enter a valid option.");
			goto Settings;
			//break;

		default :
			printf("Enter a valid option");
			getch();
			goto Main_Menu;
	}
}
