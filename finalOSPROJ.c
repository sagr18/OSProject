#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
struct process
{
	int pid,bt,wt,tat,pri;
};

int main()
{
  int n,i,n1=0,n2=0,n3=0,p=1,q=1,r=1;
  int total_waiting_time=0,total_tat=0,quant=4,quantRR=10 ;
  int c1=0,c2=0,c3=0,t=0; // for waiting times.
  int Rembt[3];		  
  printf("\t\t\t============================\n\n\t\tRange OF Queue1 Priority is 1-10 i.e Round Robin\n");
  printf("\n\t\tRange OF Queue2 Priority is 11-20 i.e Priority Scheduling\n");
  printf("\n\t\tRange OF Queue3 Priority is 21-30 i.e FCFS\n\n\n");
  printf("\t\t\t============================\n");
  printf("ENTER THE NUMBER of processes : ");
  scanf("%d",&n);
  printf("\n__________________________________\n");
  struct process p1[n],p2[n],p3[n],temp;
  printf("\nENTER Process Number | Priority | |Burst Time : \n");
  for(i=1;i<=n;i++)
  {
  	printf("\nFOR PROCESS %d\n",i);
  	struct process temp1;
  	scanf("%d",&temp1.pid);
  	scanf("%d",&temp1.bt);
  	A:
  	scanf("%d",&temp1.pri);
  	if(temp1.pri>=1 && temp1.pri<=10)
  	{
  		p3[p++]=temp1; n3++;   //n1 size of q1 
	}
	else if(temp1.pri>=11 && temp1.pri<=20)
  	{
  		p2[q++]=temp1; n2++;   //n2 size of q2
	  }
	else if(temp1.pri>=21 && temp1.pri<=30)
  	{
  		p1[r++]=temp1; n1++;  //n3 size of q3
	  }
    else
    {
    	printf("Invalid Priority\n");  
  		goto A;
	}
	
}
					/*	COPYING EACH PROCESS'S BURST TIME AND SUMS IT UP */
int s1=0,s2=0,s3=0;
for (int i = 1 ; i <= n1 ; i++){
    s1+=p1[i].bt; p1[i].wt=0;
}
for (int i = 1 ; i <= n2 ; i++){
    s2+=p2[i].bt; p2[i].wt=0;
}
for (int i = 1 ; i <= n3 ; i++){
    s3+=p3[i].bt; p3[i].wt=0;
}
Rembt[1]=s1; Rembt[2]=s2; Rembt[3]=s3;

int count_time=0; 
int bt1_Left[n1],bt2_Left[n2],bt3_Left[n3] ;

						 
for (int i=1;i<=n1;i++){
	bt1_Left[i]=p1[i].bt ;
}
for (int i=1;i<=n2;i++){
	bt2_Left[i]=p2[i].bt ;
}
for (int i=1;i<=n3;i++){
	bt3_Left[i]=p3[i].bt ;
}
 
 
        
						/*SORTING ON THE BASIS OF PRIORITIES FOR PRIORITY SCHEDULING IN QUEUE2*/
int pos,j;
for(i=1;i<=n2;i++)
{
    pos=i;
    for(j=i+1;j<=n2;j++)
    {
        if(p2[j].pri>p2[pos].pri)
        {
            pos=j;
		}
    }
    temp=p2[i];
    p2[i]=p2[pos];
    p2[pos]=temp;	
}
while (1) 
{		
	/*STARTING FROM QUEUE1 i.e K=1*/
bool Done = true;   
for (int k=1;k<=3;k++) 
{
	count_time=0;  
	if(Rembt[k]>0)  
	{ 
	Done=false ; 
	if(Rembt[k]>quantRR)
	{
	    if(k==1&&n1!=0) 
		{
        	t+=c1 ; 
            count_time=0;
   			while (1)
    		{
      			bool done = true;
      			for(int i=1;i<=n1;i++) 
       			{
             		if(bt1_Left[i]>0)
            		{
                		done=false; 
                		if (bt1_Left[i]>quant)
                		{
                  			if(count_time+quant>10)
                  			{
                  				bt1_Left[i]-=10-count_time;
								t+= 10-count_time  ; 
								count_time=10;
								break;
							}
							t+=quant; 
							count_time += quant;
                    		bt1_Left[i] -= quant;
                    			  
                		}
                		else
                		{
                			if(count_time+p1[i].bt>10)
                  			{
                  				bt1_Left[i]-= 10-count_time ;t+= 10-count_time;  
								count_time=10;
								break; 
							}
                    		t=t+bt1_Left[i];
                    		p1[i].wt += t - p1[i].bt;  
							count_time+=p1[i].bt;
			
                    			bt1_Left[i] = 0;
                	      	}
            		  }
            		  if(count_time>=10)
            		   {
            		     break; 
					   }
        		     }
                     if (done == true || count_time>=10)
                        break;
                    } 
 					printf("\nWaiting time is:%d\n",p1[i].wt) ;
 					Rembt[k] -= quantRR; 
 					c1=0; c2+=quantRR; c3+=quantRR;
 					
				 }
               	
			else if(k==2 && n2!=0)  // q2 STARTING Priority Algo.
			{
                //calculating WAITING TIME....
     			count_time=0;
        		for(i=1; i<=n2 ; i++)
        	   {
        	       if(bt2_Left[i]<=0 && bt2_Left[i+1]<=0 ) 
       		       {
       		       	 continue;
				   }
				   else if(bt2_Left[i]<=0 && bt2_Left[i+1]>0 ) 
        		   { 
						p2[i+1].wt += p2[i].bt + p2[i].wt +c2 ; continue;
				   }
				   p2[i].wt += c2 ;
				   while(bt2_Left[i]!=0)
					{
					    if(count_time==10)
					    {
					    	break;
						}
						bt2_Left[i]-= 1;
					    count_time++;
					}				   
					if(count_time>10)
					{
						break;
					}
					if(i==n2)
					{
					    break;	
					}
					if(bt2_Left[i]==0)
					{
						p2[i+1].wt = p2[i].bt + p2[i].wt ;
					}
				}
				    printf("\nhWaiting time is:%d\n",p2[i].wt) ;

                   Rembt[k]-=quantRR;
                   c2=0; 
                   c1+=quantRR; 
				   c3+=quantRR;
		          }  // end of q2  
				else if(k==3&&n3!=0) 
				{
                 //calculating WAITING TIME-------------------------
     			   count_time=0;
        		   for(i=1; i<=n3 ; i++)
        		   {
        		       if(bt3_Left[i]<=0 && bt3_Left[i+1]<=0 ) 
        		       {
        		       	 continue;
					   }
					   else if(bt3_Left[i]<=0 && bt3_Left[i+1]>0 ) 
        		       {
							 p3[i+1].wt+=p3[i].bt+p3[i].wt+c3; 
							 continue;
					   }
					     p3[i].wt+=c3 ;
					   while(bt3_Left[i]!=0)
					   {
					       if(count_time==10)
					        {
					        	break;
							}
						   bt3_Left[i]-=1;
					       count_time+=1;
						}				   
					    if(count_time>10)
					          break;
					    if(i==n3)
					    {
					      break;	
						}
						if(bt3_Left[i]==0)
						{
					    p3[i+1].wt=p3[i].bt+p3[i].wt ;
					    }
				     }
					printf("\nhWaiting time is:%d\n",p3[i].wt) ;
                   Rembt[k]-=quantRR; 
                   c1+= quantRR; 
				   c2+=quantRR; 
				   c3=0;
		          }

              }
         else
		 { 
		   if(k==1&&n1!=0)  // q1
		   {  
    			t+=c1;  	
		    	while(1)
    			{
        			bool done=true;
        			for (int i=1;i<=n1;i++) // to traverse each process.
        			{
						if(bt1_Left[i] > 0)
            			{
                			done=false; // There is a pending process in q1
 							if(bt1_Left[i]>quant)
                				{
                    				t+=quant;
                    				bt1_Left[i]-=quant;
                				}
                			else
                				{
                    				t=t+bt1_Left[i];
                    				p1[i].wt=t-p1[i].bt;
                    				bt1_Left[i]=0;
                				}
            			}
        			}
        			if(done == true)
          			{
          				 break;	
					}
    			}
		    	c1=0; 
				c2+=Rembt[k]; 
				c3+=Rembt[k];
		    	Rembt[k]=0;
						       
		      } // End of q1.
		      
		  else if(k==2&&n2!=0)  // q2
		  {
		  	 for(i=1;i<=n2;i++)
        	 {
        		if(i==1&&n2==1)
				{
					p2[i].wt+=c2;
					bt2_Left[k]=0; 
					break;
				}
				if(i==n2)
				{
					bt2_Left[i]=0; 
					break;
				}
			    if(bt2_Left[i]<=0 && bt2_Left[i+1]<=0 ) 
        		{
        		    continue;
				}
		   	    else if(bt2_Left[i]<=0 && bt2_Left[i+1]>0 ) 
        		{
					p2[i+1].wt = p2[i].bt + p2[i].wt +c2 ; 
					continue; 
				}
				p2[i].wt += c2 ;
				bt2_Left[i]=0;
				p2[i+1].wt = p2[i].bt + p2[i].wt ;
				}
				    
			 c2=0; 
			 c3+=Rembt[k]; 
			 c1+=Rembt[k];
			 Rembt[k]=0;
		   }
		   
		   else if(k==3&&n3!=0)  // q3 
		   {
		  	for(i=1;i<=n3;i++)
        	{
        		if(i==1 && n3==1)
				{
					p3[i].wt+=c3 ;bt3_Left[k]=0; break;
				}
				if(i==n3)
				{
					bt3_Left[i]=0; break;
				}
				if(bt3_Left[i]<=0 && bt3_Left[i+1]<=0 ) 
        		{
        		   	continue;
			    }
				else if(bt3_Left[i]<=0 && bt3_Left[i+1]>0 ) 
        		{
					p3[i+1].wt = p3[i].bt + p3[i].wt +c3 ; 
					continue; 
				}
				p3[i].wt += c3 ;
				bt3_Left[i]=0;
				p3[i+1].wt = p3[i].bt + p3[i].wt ;
				}
			 c3=0; 
			 c2+= Rembt[k]; 
			 c1+= Rembt[k];
			 Rembt[k]=0;
		   }
		 	
		}  
	}
      
}
if (Done == true){
	break;
}
}
 									/*CALCULATING TURNAROUND TIME*/ 
 									
int wt_sum=0,tat_sum=0;
for (int i=1;i<=n1;i++)
{	p1[i].tat=p1[i].bt+p1[i].wt;
	wt_sum+=p1[i].wt;  
	tat_sum+=p1[i].tat; 
}
for (int i=1;i<=n2;i++)
{ 
	p2[i].tat=p2[i].bt+p2[i].wt;
    wt_sum+=p2[i].wt;  
	tat_sum+=p2[i].tat;  
}
for (int i=1;i<=n3;i++)
{ 
	p3[i].tat=p3[i].bt+p3[i].wt;
    wt_sum+=p3[i].wt;  
	tat_sum+=p3[i].tat;  
} 


printf("\t\t\tCalculating the result\n\t\t\tPLEASE WAIT...");
sleep(1);
system("cls");

printf("\n\tProcess Number |\tPriority |\tBurst Time |\tWaiting Time |\tTurn Around Time");
printf("\n\nQUEUE1 : \t\n");
for (int i=1;i<=n1;i++)
{
	printf("\t%d \t\t%d \t\t%d \t\t%d \t\t%d",p1[i].pid,p1[i].pri,p1[i].bt,p1[i].wt,p1[i].tat);
}
printf("\nQUEUE2 : \t\n");
for (int i=1;i<=n2;i++)
{
	printf("\t%d \t\t%d \t\t%d \t\t%d \t\t%d",p2[i].pid,p2[i].pri,p2[i].bt,p2[i].wt,p2[i].tat);}

printf("\nQUEUE3 : \t\n");
for (int i=1;i<=n3;i++)
{
	printf("\t\t%d \t\t%d \t\t%d \t\t%d \t\t%d",p3[i].pid,p3[i].pri,p3[i].bt,p3[i].wt,p3[i].tat);
}
printf("\n");
}
