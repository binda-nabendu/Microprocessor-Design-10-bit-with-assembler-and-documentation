#include <bits/stdc++.h>
using namespace std;

string spiltFirstWord(string s){
    string word;
    int i=0;
    while(s[i]!=' '){
        word+= s[i++];
    }
    return word;
}

string registerValueGenerator(const string& s){
    if(s=="$t0")
        return "00";

    else if(s=="$t1")
        return "01";

    else if(s=="$t2")
        return "10";

    else if(s=="$zero")
        return "11";

    else return "";
}

string decimalToBinaryConverter(int offset, int maxLength){
    string binary;
    for (int i = 0; i<maxLength; i++) {
        int temp= offset % 2;
        binary = to_string(temp)+binary;
        offset = offset / 2;
    }
    return binary;
}

char octetToHexaGenerator(const string& octet){
    if(octet.length() == 2){
        if(octet == "00"){
            return '0';
        }else if(octet == "01"){
            return '1';
        } else if(octet == "10"){
            return '2';
        } else if(octet == "11"){
            return '3';
        }else{
            return ' ';
        }
    }
    else{
        if(octet == "0000"){
            return '0';
        }else if(octet == "0001"){
            return '1';
        } else if(octet == "0010"){
            return '2';
        } else if(octet == "0011"){
            return '3';
        } else if(octet == "0100"){
            return '4';
        } else if(octet == "0101"){
            return '5';
        } else if(octet == "0110"){
            return '6';
        } else if(octet == "0111"){
            return '7';
        } else if(octet == "1000"){
            return '8';
        } else if(octet == "1001"){
            return '9';
        } else if(octet == "1010"){
            return 'A';
        } else if(octet == "1011"){
            return 'B';
        } else if(octet == "1100"){
            return 'C';
        } else if(octet == "1101"){
            return 'D';
        } else if(octet == "1110"){
            return 'E';
        } else if(octet == "1111"){
            return 'F';
        } else{
            return ' ';
        }
    }
}

string binaryToHexaConv(string binaryNum){
    binaryNum.erase(remove(binaryNum.begin(), binaryNum.end(), ' '), binaryNum.end());
    string hexaValue;
    string firstOctet, secondOctet, thirdOctet;
    int i=2;
    firstOctet+=binaryNum[0];
    firstOctet+= binaryNum[1];
    while(i<6){
        secondOctet+=binaryNum[i++];
    }
    while (i<10){
        thirdOctet+=binaryNum[i++];
    }
    hexaValue = octetToHexaGenerator(firstOctet);
    hexaValue += octetToHexaGenerator(secondOctet);
    hexaValue += octetToHexaGenerator(thirdOctet);
    return hexaValue;
}

void warningMessage(){
    cerr << "\nWarning: \nThis System will give you a valid output "
            "\nwhen you give a valid set of code according to our ISA\n\n";
}

int main() {
    warningMessage();
    ifstream source;
    source.open("input.txt");
    ofstream destinationBinary;
    destinationBinary.open("machineCodeInBin.txt");

    ofstream destinationHexa;
    destinationHexa.open("output.txt");


    if(source.is_open()){
        string s;

        while(getline(source, s)){
            // instruction for ignore blank line
            if(s.length()<1)
                continue;
            //--------------------------------------

            string instruction= spiltFirstWord(s);
            string outputBin;

            if(instruction == "ADD" || instruction == "AND" || instruction == "OR"){

                // spilt instruction, source, secondary source, destination
                string words[4];
                int i=0, j=0;
                while(i<4 && j<s.length()){
                    if(s[j]==','){
                        j++;
                        continue;
                    }
                    if(s[j]==' '){
                        i++;
                        j++;
                    }else
                        words[i]+=s[j++];

                }
                //----------------------------------------------------------
                // here words[0]= Instruction, words[1]= destination,
                // words[2]= source, words[3]= secondary source;
                if(words[0]=="ADD")
                    outputBin += "000";
                else if(words[0]=="AND")
                    outputBin += "001";
                else
                    outputBin += "010";
                outputBin+= registerValueGenerator(words[2]);
                outputBin+= registerValueGenerator(words[3]);
                outputBin+= registerValueGenerator(words[1]);
                outputBin+="0";

            }

            else if(instruction=="ADDi" || instruction=="BEQ"){
                outputBin+=((instruction == "ADDi")?"011":"110");
                string rs, rt,offset;
                int temp=4;

                // spilt rt
                while(s[temp]!=','){
                    if(s[temp]==' '){
                        temp++;
                    }else{
                        rt+=s[temp++];
                    }
                }
                //------------
                temp++;
                // spilt rs
                while(s[temp]!=','){
                    if(s[temp]==' '){
                        temp++;
                    }else{
                        rs+=s[temp++];
                    }
                }
                //------------
                temp++;
                // spilt offset
                while (temp<s.length()){
                    if(s[temp]>=48 && s[temp]<56){
                        offset+=s[temp];
                        break;
                    }
                    temp++;
                }
                //------------
                outputBin += ((instruction == "ADDi")?registerValueGenerator(rs): registerValueGenerator(rt));
                outputBin += ((instruction == "ADDi")?registerValueGenerator(rt):registerValueGenerator(rs));
                outputBin += decimalToBinaryConverter(stoi(offset), 3);
            }

            else if(instruction == "J"){
                outputBin+= "111";
                string largeOffset;
                int temp=1;
                while(temp<s.length()){
                    largeOffset += s[temp++];
                }
                outputBin+= decimalToBinaryConverter(stoi(largeOffset), 7);
            }

            else if(instruction == "LW"){
                outputBin = "100";
                int temp=2;
                string rs,rt,offset;
                // spilt rt
                while(s[temp]!=','){
                    if(s[temp]==' '){
                        temp++;
                    }else{
                        rt+=s[temp++];
                    }
                }
                //------------
                temp++;
                // spilt offset
                while (s[temp] !='('){
                    if(s[temp]>=48 && s[temp]<56){
                        offset+=s[temp];
                    }
                    temp++;
                }
                //------------
                temp++;
                //spilt rt
                while (s[temp] != ')') {
                    rs += s[temp++];
                }
                //------------
                outputBin += registerValueGenerator(rs);
                outputBin += registerValueGenerator(rt);
                outputBin += decimalToBinaryConverter(stoi(offset), 3);

            }

            else if(instruction == "SW"){
                outputBin = "101";
                int temp=2;
                string rs,rt,offset;
                // spilt rs
                while(s[temp]!=','){
                    if(s[temp]==' '){
                        temp++;
                    }else{
                        rt+=s[temp++];
                    }
                }
                //------------
                temp++;
                // spilt offset
                while (s[temp] !='('){
                    if(s[temp]>=48 && s[temp]<56){
                        offset+=s[temp];
                    }
                    temp++;
                }
                //------------
                temp++;
                //spilt rt
                while (s[temp] != ')') {
                    rs += s[temp++];
                }
                //------------

                outputBin += registerValueGenerator(rs);
                outputBin += registerValueGenerator(rt);
                outputBin += decimalToBinaryConverter(stoi(offset), 3);
            }

            else{
                cerr << "\nUndefined instruction: " << s <<"\n";
                continue;
            }
            destinationBinary << outputBin << endl;
            destinationHexa << binaryToHexaConv(outputBin) << endl;
        }
    }else{
        cout << "Sorry This file will be corrupted";
    }
    return 0;
}
