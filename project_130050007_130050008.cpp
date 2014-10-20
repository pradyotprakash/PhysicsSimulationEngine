/* 1. The program works only when approrpriate values are given as input.
 * 2. The magnitude of the charge should not be greater than 0.01 C
 * 3. All the input values would be taken in their SI Units.
 * 4. The particle is reflected when it hits the boundary.
 * 5. A sample input file has also been added.
*/
#include <simplecpp>
#include <fstream>


int total = 0;
const int N = 20;
const long double k = 1/(4*PI*8.85418782E-12);
const int radius = 1, res = 700, iterations = 20000, dist = 10;
const long double dt = 0.001;
const long double mu = pow(10,-7);

		

class body
{
	public:
	string name;
	long double charge, vx[2], vy[2], mass, accx, accy;
	long double x[2],y[2];
	body()
	{
		name="";
		charge=0;
		vx[0]=0;vx[1]=0;
		vy[0]=0;vy[1]=0;
		x[0]=0;x[1]=0;
		y[0]=0;y[1]=0;
		mass=1;
	}
};

body obj[N];

class operations
{
	public:
	
		
	//converts integer to string
	string itos(int a,int b)
	{
		string s1="000";
		int i=2;
		do
		{
			int d=a%10;
			s1[i]=char(d+48);
			--i;
			a/=10;
		}while(a!=0);
	
		string s2="000";
		i=2;
		do
		{
			int d=b%10;
			s2[i]=char(d+48);
			--i;
			b/=10;
		}while(b!=0);
		string s="("+s1+","+s2+")";
		return s;
	}

		
	void displayAndInput()
	{
		int check = 0;
		string name; 
		initCanvas("Electromagnetic Simulator",res,res);
		Text txt1[10];
		Rectangle r1[2];
		int x11=res/2-150, x12=res/2-50, y11=215, y12=265;
		int x21=res/2+50, x22=res/2+150, y21=215, y22=265;

			
		txt1[0].init(res/2,50,"Welcome to Electromagnetic Simulator!");
		txt1[1].init(res/2,60,"------------------------------------");
		txt1[2].init(res/2,80,"This tool lets you simulate the motion of charged");
		txt1[3].init(res/2,100,"particles under their own electric and magnetic fields.");
		txt1[4].init(res/2,160,"Specify the mode of entering data for the particles by clicking on the relevant box");
		r1[0].init(res/2-100,240,100,50);
		r1[1].init(res/2+100,240,100,50);
		txt1[5].init(res/2-100,235,"File Input");
		txt1[6].init(res/2-100,250,"(For accuracy)");
		txt1[7].init(res/2+100,235,"Window Input");
		txt1[8].init(res/2+100,250,"(For ease)");
		//waits until correct coordinates are clicked
		while(check == 0)
		{
			int coor=getClick();
			int x=coor/65536;
			int y=coor%65536;
			if( (x>=x11 && x<=x12) && (y>=y11) && (y<=y12) ) {check=1;}
			else if( (x>=x21 && x<=x22) && (y>=y21) && (y<=y22) ) {check=2;}
		}
		//if file input is clicked
		if(check == 1)
		{
			closeCanvas();
			initCanvas("Electromagnetic Simulator",res,res);
			Text txt(res/2,res/2-20,"Enter the data through the file name 'data' present in the same directory.");
			Text txt1(res/2,res/2,"Click on this window after you do it");
			getClick();
			wait(0.5);
			ifstream inp("data",ios::in);
			for(int i=1;i<=7;++i) inp>>name;
			while(inp>>obj[total].name)
			{
				inp>>obj[total].mass;
				inp>>obj[total].charge;
				inp>>obj[total].x[0];obj[total].x[1]=obj[total].x[0];
				obj[total].x[0]-=40;obj[total].x[1]-=40;obj[total].y[0]-=40;obj[total].y[1]-=40;
				inp>>obj[total].y[0];obj[total].y[1]=obj[total].y[0];
				inp>>obj[total].vx[0];obj[total].vx[1]=obj[total].vx[0];
				inp>>obj[total].vy[0];obj[total].vy[1]=obj[total].vy[0];
				++total;
			}
			inp.close();
			closeCanvas();
		}
		//if window input is chosen
		else
		{
			//previous canvas closed
			closeCanvas();
			string check1 = "1";
			//get input
			while(check1 != "0")
			{				
				initCanvas("Electromagnetic Simulator",res+50,res+50);
				Turtle t;
				t.hide();t.penUp();
				t.moveTo(40,40);t.penDown();
				repeat(4){
				t.forward(res);t.right(90);
			    }
				Text txt1(res/2+25,res/2,"Click on the window to get the coordinates of that point.");
				Text txt2(res/2+25,res/2+20,"Double click at the point to specify the coordinates of the particle");
				Text txt3(res/2+25,res/2+40,"and enter the corresponding data in Terminal!");
				wait(3);
				txt1.reset(35,30,"(0,0)");
				txt2.reset(res+30,30,"(700,0)");
				txt3.reset(20,res+40,"(0,700)");
				int g,h;
				int coor;
				Text txt;
				XEvent event;
				while(getClick())
				{
					nextEvent(&event);
					int p=MousePosX(event)-40;
					int q=MousePosY(event)-40;
					txt.reset(res/2,20,itos(p,q));
					if(p==g && q==h)
					{
						break;
					}
					g=p;h=q;
				}
				
				
				coor = getClick();
				int x = coor/65536 - 40;
				int y = coor%65536 - 40;
				cout<<x<<" "<<y<<endl;
				Circle q(x,y,2);
				q.setFill(true);
				obj[total].x[0] = x; obj[total].x[1]=x;
				obj[total].y[0] = y; obj[total].y[1] = y;
				for(int i=1;i<=50;++i) {cout<<endl;}
				wait(0.5);
				closeCanvas();
				cout<<"Enter the data for particle "<<total+1<<endl;
				cout<<"Name : ";
				cin>>obj[total].name;
				cout<<"Mass : ";
				cin>>obj[total].mass;
				cout<<"Charge : ";
				cin>>obj[total].charge;
				cout<<"x-component of velocity : ";
				cin>>obj[total].vx[0];obj[total].vx[1]=obj[total].vx[0];
				cout<<"y-component of velocity : ";
				cin>>obj[total].vy[0];obj[total].vy[1]=obj[total].vy[0];
				++total;
				cout<<"Press '0' to stop entering values or anything else to continue entering values :\n";
				cin>>check1;
			}
		}
		
	}
};
	

class data
{
	public:
	
	long double x,y,z;
	
	data()
	{
		x=0; 
		y=0; 
		z=0;
	}
	
	data(long double a, long double b, long double c)
	{
		x=a;
		y=b;
		z=c;
	}
	
	double operator&(data b)
	{
		return (x*b.x + y*b.y + z*b.z);
	}
	
	void electricField(body obj[], long double x, long double y, long double &fx, long double &fy)
	{
		fx=0;
		fy=0;
		long double theta, r, field;
		for(int i=0;i<total;++i)
		{
			if((x!=obj[i].x[0]) || (y!=obj[i].y[0]))
			{
				r =  (pow((x-obj[i].x[0]),2)) + (pow((y-obj[i].y[0]),2)) ;
				theta = atan2( (y-obj[i].y[0]),(x-obj[i].x[0]) );
				field = k*obj[i].charge/r;
				fx+=field*cos(theta);
				fy+=field*sin(theta);
			}
		}
	}
	
	void magneticField(int w, body *obj, long double &fmx, long double &fmy)
	{
		data p,q;
		long double charge;
		fmx=0;
		fmy=0;
			
		for(int i=0;i<total;++i)
		{
			charge=obj[i].charge;
			if(i!=w)
			{
				p=data(obj[w].vx[0],obj[w].vy[0],0);
				double x1=obj[w].x[0]-obj[i].x[0];
				double y1=obj[w].y[0]-obj[i].y[0];
				double z1=0;
				q=data(x1,y1,z1);
				double val1 = (p&q)*charge;
				q=data(obj[i].vx[0],obj[i].vy[0],0);
				double val2 = (p&q)*charge;
				fmx+= mu*(val1 * obj[i].vx[0] - val2 * x1);
				fmy+= mu*(val1 * obj[i].vy[0] - val2 * y1);
			}
		}
	}
	
};


int main()
{
	data dat;
	bool flag = false;
	long double fx=0, fy=0, fmx=0, fmy=0, extelecfx=0,extelecfy=0, extmagf=0;
	operations oper;
	
	//user interface
	{
		oper.displayAndInput();
		
		initCanvas("Electromagnetic Simulator",res,res);
		Text lk(res/2,res/2,"Now enter the external Electromagnetic field data via terminal");
		wait(1.5);
		closeCanvas();
		cout<<"Enter the x and y components of external electric field : ";
		cin>>extelecfx>>extelecfy;
		cout<<"Enter the z component of external magnetic field (towards you is positive) : ";
		cin>>extmagf;
		
	}	
	   
	initCanvas("Electromagnetic Simulator",res+50,res+50);
	Circle c[N];
	Text t[N];
	Text txta(35,30,"(0,0)");
	Text txtb(res+30,30,"(700,0)");
	Text txtc(20,res+40,"(0,700)");
				
	Turtle tur;
	tur.hide();tur.penUp();
	tur.moveTo(40,40);tur.penDown();
	repeat(4){
	tur.forward(res);tur.right(90);
	}
	
	for(int i=0;i<total;++i)
	{
		if(obj[i].mass != 0)//representing the particle on the canvas
		{
			c[i].init(obj[i].x[1], obj[i].y[1],radius);
			if(obj[i].charge>0) {c[i].setColor(COLOR("blue"));}
			else if(obj[i].charge<0) {c[i].setColor(COLOR("red"));}
			else {c[i].setColor(COLOR("green"));}
			c[i].setFill(true);
			t[i].init(obj[i].x[1], obj[i].y[1], obj[i].name);
			if(obj[i].charge>0) {t[i].setColor(COLOR("blue"));}
			else if(obj[i].charge<0) {t[i].setColor(COLOR("red"));}
			else {t[i].setColor(COLOR("green"));}
			
		}
	}
	
	if(total!=0)
	{
	for(int z=1;z<=iterations;++z)//motion of the particle
	{
		for(int i=0;i<total;++i)
		{
			//electric field wala part
			dat.electricField(obj,obj[i].x[0], obj[i].y[0], fx, fy);
			//magnetic field wala part
		    dat.magneticField(i,obj,fmx,fmy);
			obj[i].accx = (fx+fmx+extelecfx+extmagf*obj[i].vy[0])*obj[i].charge/obj[i].mass;
			obj[i].accy = (fy+fmy+extelecfy-extmagf*obj[i].vx[0])*obj[i].charge/obj[i].mass;
			obj[i].x[1]=obj[i].x[0]+obj[i].vx[0]*dt + obj[i].accx*dt*dt*0.5;
			obj[i].y[1]=obj[i].y[0]+obj[i].vy[0]*dt + obj[i].accy*dt*dt*0.5;
			obj[i].vx[1] = obj[i].vx[0] + obj[i].accx*dt;
			obj[i].vy[1] = obj[i].vy[0] + obj[i].accy*dt;
			c[i].imprint();
			c[i].reset(obj[i].x[1], obj[i].y[1], radius);
			t[i].reset(obj[i].x[1], obj[i].y[1], obj[i].name);
								 
			
			for(int j=0; j<total; ++j)//part dealing with collisions
			{
				if(j!=i)
				{
					if(pow((pow((obj[j].x[0]-obj[i].x[0]),2)+pow((obj[j].y[0]-obj[i].y[0]),2)),0.5)<=2 && obj[j].charge!=0)
					{
						flag=true;
						break;
					}
				}
			
				
				if(flag==true)
				{
					//if((obj[i].vx!=obj[j].vx)&&(obj[i].vy!=obj[j].vy))
					//{	
						obj[i].vx[1]=((obj[i].mass*obj[i].vx[0])+(obj[j].mass*obj[j].vx[0]))/(obj[i].mass+obj[j].mass);
						obj[i].vy[1]=((obj[i].mass*obj[i].vy[0])+(obj[j].mass*obj[j].vy[0]))/(obj[i].mass+obj[j].mass);
						obj[i].accx=((obj[i].mass*obj[i].accx)+(obj[j].mass*obj[j].accx))/(obj[i].mass+obj[j].mass);
						obj[i].accy=((obj[i].mass*obj[i].accy)+(obj[j].mass*obj[j].accy))/(obj[i].mass+obj[j].mass);
						obj[i].mass=obj[i].mass+obj[j].mass;
						obj[i].charge=obj[i].charge+obj[j].charge;
						obj[j].charge=0;
						obj[j].vx[0]=0;obj[j].vx[1]=0; 
						obj[j].vy[0]=0;obj[j].vy[1]=0; 
						obj[j].accx=0; obj[j].accy=0;
						
					//}
				}
				flag=false;
			}
			
			if((obj[i].x[1]<=40) || (obj[i].x[1]>=res+40)) {obj[i].vx[1]=(-obj[i].vx[1]); obj[i].accx=(-obj[i].accx);}
			if((obj[i].y[1]<=40) || (obj[i].y[1]>=res+40)) {obj[i].vy[1]=(-obj[i].vy[1]); obj[i].accy=(-obj[i].accy);}
			
		}
		
		for(int i=0; i<total; i++)
		{
			obj[i].x[0]=obj[i].x[1];
			obj[i].y[0]=obj[i].y[1];
			obj[i].vx[0]=obj[i].vx[1];
			obj[i].vy[0]=obj[i].vy[1];
		}
	}
	}
	else {
		
		Text txt(res/2,res/2,"No particles entered!");
		wait(2);
		
	}
	
	//close the program
	for(int i=0;i<total;++i) {c[i].hide(); t[i].hide();}
	
	{
		Text txt(res/2,res/2,"Click on the Window to Exit!");
		getClick();
	}
	
	Text txt1(res/2,res/2,"Thank You for using this Tool!");
	wait(2);
	closeCanvas();
	return 0;
}
