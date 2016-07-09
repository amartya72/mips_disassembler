//
//  main.cpp
//  mips_disassembler
//
//  Created by Rick on 3/1/15.
//  Copyright (c) 2015 Rick. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


using namespace std;

int addr=496;
int break_flag=0;
ofstream out("result.txt"); //enter the destination where you want to save your file

string compliment(string number)
{
    bool carry = true;
    if (number[0]=='1') {
        for(long int i=number.size()-1;i>=0;i--) {
        number[i] = number[i] == '0' ? '1' : '0';
    
            if(number[i]=='0' && carry){
                number[i]='1';
                carry=false;
            }
        
            else if(number[i]=='1' && carry){
                number[i]='0';
                carry=true;
            }
        }
    number="-"+number;
    }
    return number;
}

void mips_diss(string instr) {
    
    //out.open("result.txt");
    string opcode,r1,r2,r3,r4,off_set,special,imme,code,jinstr,instruction;
    
    signed long int rs,rt,rd,base,sa,off,immed;
    signed long int jinstri;
    opcode=instr.substr(0,6);
    r1=instr.substr(6,5);
    r2=instr.substr(11,5);
    r3=instr.substr(16,5);
    r4=instr.substr(21,5);
    special=instr.substr(26,6);
    off_set=r3+r4+special;
    imme=r3+r4+special;
    jinstr=r1+r2+r3+r4+special;
    instruction=opcode+r1+r2+r3+r4+special;
    code=opcode+" "+r1+" "+r2+" "+r3+" "+r4+" "+special;
    
    if(break_flag==1){
        //signed int temp;
        
        signed int temp;
        temp=stol(instr,nullptr,2);
        out << instruction<< "\t" << addr<<"\t"<<temp<<endl;
        
    }
    

    else if (opcode=="001000")  {
        
        rs=stoi(r1,nullptr,2);
        rt=stoi(r2,nullptr,2);
        imme=compliment(imme);
        immed=stol(imme,nullptr,2);
        
        out << code<< "\t" << addr<<"\t"<<"ADDI"<<"\tR"<<rt<<", R"<<rs<<", #"<<immed <<endl;
    }
    
    else if (opcode=="001001"){
       
        rs=stoi(r1,nullptr,2);
        rt=stoi(r2,nullptr,2);
        imme=compliment(imme);
        immed=stol(imme,nullptr,2);

        out << code<< "\t" << addr<<"\t"<<"ADDIU"<<"\tR"<<rt<<", R"<<rs<<", #"<<immed <<endl;
    }
    
    else if (opcode=="000100"){
        
        rs=stoi(r1,nullptr,2);
        rt=stoi(r2,nullptr,2);
        imme=compliment(imme);
        imme=imme+"00";
        immed=stol(imme,nullptr,2);
        
        out << code<< "\t" << addr<<"\t"<<"BEQ"<<"\tR"<<rs<<", R"<<rt<<", #"<<immed <<endl;
    }

    else if (opcode=="000111"){
        
        rs=stoi(r1,nullptr,2);
        imme=compliment(imme);
        imme=imme+"00";
        immed=stol(imme,nullptr,2);
        
        out << code<< "\t" << addr<<"\t"<<"BGTZ"<<"\tR"<<rs<<", #"<<immed <<endl;
    }
    
    else if (opcode=="000110"){
        
        rs=stoi(r1,nullptr,2);
        imme=compliment(imme);
        imme=imme+"00";
        immed=stol(imme,nullptr,2);
        
        out << code<< "\t" << addr<<"\t"<<"BLEZ"<<"\tR"<<rs<<", #"<<immed <<endl;
    }
    
    else if (opcode=="000101"){
        
        rs=stoi(r1,nullptr,2);
        rt=stoi(r2,nullptr,2);
        imme=compliment(imme);
        imme=imme+"00";
        immed=stol(imme,nullptr,2);
        
        out << code<< "\t" << addr<<"\t"<<"BNE"<<"\tR"<<rs<<", R"<<rt<<", #"<<immed <<endl;
    }

    else if (opcode=="001010"){
        
        rs=stoi(r1,nullptr,2);
        rt=stoi(r2,nullptr,2);
        imme=compliment(imme);
       immed=stol(imme,nullptr,2);
        
        out << code<< "\t" << addr<<"\t"<<"SLTI"<<"\tR"<<rt<<", R"<<rs<<", #"<<immed <<endl;
    }
    
//Start Special cases
    
    else if (opcode=="000000"){
    
        if (special=="100000") {
            rd=stoi(r3,nullptr,2);
            rs=stoi(r1,nullptr,2);
            rt=stoi(r2,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"ADD"<<"\tR"<<rd<<", R"<<rs<<", R"<<rt <<endl;
        }
        
        else if (special=="100001"){
            rd=stoi(r3,nullptr,2);
            rs=stoi(r1,nullptr,2);
            rt=stoi(r2,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"ADDU"<<"\tR"<<rd<<", R"<<rs<<", R"<<rt <<endl;
        }
    
        else if (special=="100100"){
            rd=stoi(r3,nullptr,2);
            rs=stoi(r1,nullptr,2);
            rt=stoi(r2,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"AND"<<"\tR"<<rd<<", R"<<rs<<", R"<<rt <<endl;
        }

        else if (special=="100111"){
            rd=stoi(r3,nullptr,2);
            rs=stoi(r1,nullptr,2);
            rt=stoi(r2,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"NOR"<<"\tR"<<rd<<", R"<<rs<<", R"<<rt <<endl;
        }

        else if (special=="100101"){
            rd=stoi(r3,nullptr,2);
            rs=stoi(r1,nullptr,2);
            rt=stoi(r2,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"OR"<<"\tR"<<rd<<", R"<<rs<<", R"<<rt <<endl;
        }

        else if (special=="100110"){
            rd=stoi(r3,nullptr,2);
            rs=stoi(r1,nullptr,2);
            rt=stoi(r2,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"XOR"<<"\tR"<<rd<<", R"<<rs<<", R"<<rt <<endl;
        }

        else if (special=="101010"){
            rd=stoi(r3,nullptr,2);
            rs=stoi(r1,nullptr,2);
            rt=stoi(r2,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"SLT"<<"\tR"<<rd<<", R"<<rs<<", R"<<rt <<endl;
        }
        
        
        else if (special=="001101" && break_flag==0){//need to add flag
            
            break_flag=1;
            out << code<< "\t" << addr<<"\t"<<"BREAK"<<endl;
        }
        
        else if (special=="001000"){
            
            rs=stoi(r1,nullptr,2);
            
            out << code<< "\t" << addr<<"\t"<<"JR"<<"\tR"<<rs<<endl;
        }
        
        else if (special=="000000" && r1!="00000" &&r2!="00000" && r3!="00000" &&r4!="00000"){
            rd=stoi(r3,nullptr,2);
            sa=stoi(r4,nullptr,2);
            rt=stoi(r2,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"SLL"<<"\tR"<<rd<<", R"<<rt<<", #"<<sa <<endl;
        }
        
        else if (special=="000011"){
            rd=stoi(r3,nullptr,2);
            sa=stoi(r4,nullptr,2);
            rt=stoi(r2,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"SRA"<<"\tR"<<rd<<", R"<<rt<<", #"<<sa <<endl;
        }
        
        else if (special=="100010"){
            rd=stoi(r3,nullptr,2);
            rs=stoi(r1,nullptr,2);
            rt=stoi(r2,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"SUB"<<"\tR"<<rd<<", R"<<rs<<", R"<<rt <<endl;
        }
        
        else if (special=="100011"){
            rd=stoi(r3,nullptr,2);
            rs=stoi(r1,nullptr,2);
            rt=stoi(r2,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"SUBU"<<"\tR"<<rd<<", R"<<rs<<", R"<<rt <<endl;
        }
        
        
        else if (special=="000000" && r1=="00000" && r2=="00000" && r3=="00000" && r4=="00000"){
            
            out << code<< "\t" << addr<<"\t"<<"NOP"<<endl;
        }
        

    }
//end special cases
    
    else if (opcode=="100011"){
        
        base=stoi(r1,nullptr,2);
        rt=stoi(r2,nullptr,2);
        off=stoi(off_set,nullptr,2);
        
        out << code<< "\t" << addr<<"\t"<<"LW"<<"\tR"<<rt<<", "<<off<<"(R"<<base<<")" <<endl;
    }
    
    
    else if (opcode=="101011"){
        
        base=stoi(r1,nullptr,2);
        rt=stoi(r2,nullptr,2);
        off=stoi(off_set,nullptr,2);
        
        out << code<< "\t" << addr<<"\t"<<"SW"<<"\tR"<<rt<<", "<<off<<"(R"<<base<<")" <<endl;
    }
    
    else if (opcode=="000010"){
        
        jinstr=jinstr+"00";
        jinstri=stoi(jinstr,nullptr,2);
        
        out << code<< "\t" << addr<<"\t"<<"J"<<"\t#"<<jinstri<<endl;
    }
    
    else if (opcode=="000001"){
        
        if(r2=="00001"){
            
            rs=stoi(r1,nullptr,2);
            off_set=compliment(off_set);
            off_set=off_set+"00";
            off=stoi(off_set,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"BGEZ"<<"\tR"<<rs<<", #"<<off<<endl;
        }
        
        
        else if(r2=="00000"){
            
            rs=stoi(r1,nullptr,2);
            off_set=compliment(off_set);
            off_set=off_set+"00";
            off=stoi(off_set,nullptr,2);
            out << code<< "\t" << addr<<"\t"<<"BLTZ"<<"\tR"<<rs<<", #"<<off<<endl;
        }
    }
    
    
}


int main(){
    
    ifstream instrset;
    instrset.open("fib_bin.txt"); //please enter your path name from where you want to read the file
    
    if(instrset.fail()){
        cerr<<"Error opening file"<<endl;
        exit(1);
    }
    
    string instr;
    while(getline(instrset,instr)){
            
       // instrset>>instr;
        mips_diss(instr);
        addr+=4;
        
    }
    
    instrset.close();
    
    return 0;
}











