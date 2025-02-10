// Copyright (C) 2025 shicj (shicj0927@github.com)
//
// This file is part of the project Super Hacker V1.0. This 
// library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public 
// License as published by the Free Software Foundation; 
// either version 3, or (at your option) any later version.

/*
files

+SuperHacker
|---hacker.exe
|---checker.exe
|---data.exe
|--+src
|  |---[name1].exe
|  |---[name2].exe
|  |---[...  ].exe
|--+dat
   |--+[seed]
      |--+[id]
	     |---data.in
		 |---[name1].out
		 |---[name2].out
		 |---[...  ].out
		 |---result.txt
*/

#include<bits/stdc++.h>
using namespace std;
string intToStr(int x){
	if(x==0)return "0";
	string s="";
	while(x){
		s=char(x%10+'0')+s;
		x/=10;
	}
	return s;
}
void system(string s){
	cerr<<"run command : "<<s<<endl;
	system(s.c_str());
}
void mkdir(string s){
	system("md .\\"+s);
}
void newf(string s){
	system("copy nul \""+s+"\"");
}
void run(string exe,string in,string out){
	newf(out);
	system(exe+"<"+in+">"+out);
}
void run(string exe){
	system(exe);
}
int n;
string players[200];
string playersf[200];
int main(){
	cout<<"Super Hacker V1.0 by shicj"<<endl;
	cout<<endl;
	cout<<"This project is for codeforces hacking."<<endl;
	cout<<"It can help you hack many people's code at the same time by using random data and check the result."<<endl;
	cout<<endl;
	cout<<"First, input the number of people: ";
	cin>>n;
	cout<<endl;
	cout<<"Then, input each people's file name (you needn't to input \".cpp\" or \".exe\")"<<endl;
	for(int i=1;i<=n;i++){
		cout<<i<<": ";
		cin>>players[i];
		playersf[i]="src\\"+players[i];
	}
	long long seed=time(0);
	mt19937 Rand(seed);
	cout<<endl;
	cout<<"Now use seed="<<seed<<", press enter to start...";
	cin.get();cin.get();
	int id=0;
	string f1="dat";
	string f2=intToStr(seed);
//	mkdir(f1);
	mkdir(f1+"\\"+f2);
	while(true){
		id++;
		cout<<"Haking #"<<id<<endl;
		seed=Rand();
		ofstream SEED(".seed");
		SEED<<seed;
		SEED.close();
		string f3=intToStr(id);
		string f=f1+"\\"+f2+"\\"+f3;
		mkdir(f);
		run("data.exe",".seed",f+"\\"+"data.in");
		for(int i=1;i<=n;i++){
			cout<<"Running "<<players[i]<<"..."<<endl;
			run(playersf[i],f+"\\"+"data.in",f+"\\"+players[i]+".out");
		}
		int result[200][200];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i>=j){
					result[i][j]=2;
					cout<<i<<" and "<<j<<" needn't to check"<<endl;
				}
				else{
					ofstream CHECKER(".checker");
					CHECKER<<f<<"\\"<<players[i]<<".out"<<endl;
					CHECKER<<f<<"\\"<<players[j]<<".out"<<endl;
					CHECKER.close();
					cout<<"checking "<<players[i]<<" and "<<players[j]<<"..."<<endl;
					run("checker");
					ifstream RESULT(".result");
					RESULT>>result[i][j];
					RESULT.close();
				}
			}
		}
		ofstream RESULT("result.txt");
		cout<<endl;
		cout<<"Result"<<endl;
		RESULT<<"Result"<<endl;
		cout<<"seed="<<seed<<endl;
		RESULT<<"seed="<<seed<<endl;
		cout<<endl;
		RESULT<<endl;
		for(int i=1;i<=n;i++){
			cout<<i<<": "<<players[i]<<endl;
			RESULT<<i<<": "<<players[i]<<endl;
		}
		cout<<endl;
		RESULT<<endl;
		for(int i=1;i<=n;i++){
			cout<<"\t"<<i;
			RESULT<<"\t"<<i;
		}
		cout<<endl;
		RESULT<<endl;
		bool flag=false;
		for(int i=1;i<=n;i++){
			cout<<i<<"\t";
			RESULT<<i<<"\t";
			for(int j=1;j<=n;j++){
				int nr=result[i][j];
				string r=nr==2?"-":(nr==1?"S":(nr==0?"D":"E"));
				cout<<r<<"\t";
				RESULT<<r<<"\t";
				if(r=="E"||r=="D"){
					flag=true;
				}
			}
			cout<<endl;
			RESULT<<endl;
		}
		if(flag){
			cout<<"Something has found!"<<endl;
			RESULT<<"Something has found!"<<endl;
			cout<<"See the data files: "<<f<<" for more info!"<<endl;
			RESULT.close();
			cin.get();cin.get();
		}
		else{
			cout<<"All same!"<<endl;
			RESULT<<"All same!"<<endl;
			RESULT.close();
		}
	}
	return 0;
}
