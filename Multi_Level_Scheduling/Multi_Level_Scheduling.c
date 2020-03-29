#include<stdio.h>

int n,p=0,q=0,r=0,tq,atflag=0;

struct process{
	int a_time,b_time,rem_time,comp_time;
}s[10],f[10],a[20];




int arrivalTime(int i){
	int h,m,at;
	printf("Enter the arrival time of the %d process (HH:MM) : ",i+1);
	scanf("%02d:%02d",&h,&m);
	if((h==10||h==11)&&(m>=0 && m<60))
	atflag=1;
	if((h==12)&&(m==0))
	atflag=1;
	at=(h*60)+m;
	if(atflag==0){
		printf("\nPlease enter the arrival time correctly between 10:00 AM to 12:00 PM");
        exit(0);
	}
	else if(atflag==1){
		atflag=0;
		return at;
	}
}


void merge(){
	int ip,iq,min,flag;
	if(p!=0 && q!=0){
		while(ip<p && iq<q){
			if(f[iq].a_time==s[ip].a_time){
				a[r]=f[iq];
				r++;
				iq++;
				a[r]=s[ip];
				r++;
				ip++;
			}
			else if(f[iq].a_time<s[ip].a_time){
				a[r]=f[iq];
				r++;
				iq++;
			}
			else if(f[iq].a_time>s[ip].a_time){
				a[r]=s[ip];
				r++;
				ip++;
			}
		}
		if(r!=(p+q)){
			if(q!=iq){
				while(iq!=q){
					a[r]=f[iq];
					r++;
					iq++;
				}
			}
			else if(p!=iq){
				while(ip!=p){
					a[r]=s[ip];
					r++;
					ip++;
				}
			}
		}
	}
	else if(q==0){
		while(ip!=p){
			a[r]=s[ip];
			r++;
			ip++;
		}
	}
	else if(p==0){
		while(iq!=q){
			a[r]=f[iq];
			r++;
			iq++;
		}
	}
}

void roundRobin(){
	int time=a[0].a_time,R=0,i,z=0,y,rc;
	while(time!=120 && R!=r){
		for(i=0;i<=z;i++){
			if(a[i].rem_time<=tq){
				time+=a[i].rem_time;
				a[i].rem_time=0;
				a[i].comp_time=time;
				R++;
			}
			else if(a[i].rem_time>tq){
				time+=tq;
				a[i].rem_time-=tq;
			}
		}
		y=z+1;
		for(rc=y;rc<r;rc++){
			if(a[rc].a_time<=time)
				z++;
		}
	}
}


void main(){


	int i,sf,at;
	printf("Enter number of process : ");
    	scanf("%d",&n);
    	if(n==0){
    	printf("No queries to be processed :(");
        exit(0);
	}
	printf("Enter 0 if you are a student or 1 if you are a faculty \n");
	for(i=0;i<n;i++){
		printf("\nstudent or faculty? : ");
		scanf("%d",&sf);
		if(sf==0){
			at=arrivalTime(i);
			s[p].a_time=at-600;
			printf("Enter the burst time of the %d process : ",i+1);
			scanf("%d",&s[p].b_time);
			s[p].rem_time=s[p].b_time;
			p++;
		}
		else if(sf==1){
			at=arrivalTime(i);
			f[q].a_time=at-600;
			printf("Enter the burst time of the %d process : ",i+1);
			scanf("%d",&f[q].b_time);
			f[q].rem_time=f[q].b_time;
			q++;
		}
		else{
			printf("\nEnter either 0 or 1 only...");
        	exit(0);
		}
	}
	printf("\nEnter the time quantum for the process : ");
	scanf("%d",&tq);

	merge();
	roundRobin();


	int total=0,sum=0,h,m;
	double avg;
	printf("\nArrival Time\tBurst Time\tTurnaround Time\tWaiting time");
	for(i=0;i<r;i++){
		h=(a[i].a_time+600)/60;
		m=(a[i].a_time+600)%60;
		printf("\n%02d:02d\t\t%d\t\t%d\t\t%d\t\t\t%d",h,m,a[i].b_time,(a[i].comp_time-a[i].a_time),(a[i].comp_time-a[i].b_time));
		total=a[i].comp_time;
		sum+=a[i].comp_time-a[i].a_time;
	}
	avg=sum/r;
	printf("\nTotal time spent for solving all queries : %d",total);
	printf("\nAverage query time : %f",avg);
}




