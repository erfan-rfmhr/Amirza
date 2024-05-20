#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<iomanip>
#include<ctime>
#include<cstdlib>
using namespace std;

string int_to_char(int&);    //the function converts int variable to char
void save_info(int , int , int , string &);

void main_menu();           //function shows the main menu
void signup();
void login();
void ranking();
void challenge();

int challenge_turn_player1(string, string);
int challenge_turn_player2(string, string);

void internal_menu();       //function shows the internal menu
void continue_game();

void show_current_game_map(string &, string &, string &);
int search_subwords(string &, string &, int &, int &);
int add_coin_by_subwords(int &);
void shuffle(string &);

void choose_level();
void wheel_of_luck();
void edit_profile();

string temp = "", temp2 = "";

int line = 1;
int last_line = 0;

string username, password, level, money, eWord, chance;     /* "level" shows player's current level,
                                                            "eWord" shows number of extra words which player has used 
                                                            "chance" shows number of chances player have */

char choice;

string challeng_answers1 = "";
string challeng_answers2 = "";

string allAnswers = "";

bool flag;
bool help = false;



int main(){`

    fstream members("user.txt");

    while(members >> temp)
        last_line++;

    members.close();
    
    cout<<"\n      < Welcome >\n"
        <<"----------------------------\n\n";

    cout<<"***************************\n"
        <<"*          Amirza         *\n"
        <<"***************************\n\n";

    cout<<"------------------------------\n"
        <<"| Developed by Erfan Arefmehr |\n"
        <<"------------------------------\n";

    main_menu();

    cin>> choice;

    while(choice != '5'){

        switch (choice){

            case '1':
                signup();
                break;

            case '2':
                login();
                username = ""; password = ""; eWord = ""; chance = ""; level = ""; line = 1;
                break;

            case '3':
                ranking();
                break;

            case '4':
                cout<<"\nWelcome to challenge mode";
                challenge();
                challeng_answers1 ="";
                challeng_answers2 = "";
                break;

            default:
                cout<<"\n\nEntered Number is Wrong! Please Enter number between(1 - 5).\n\n";
        }

        main_menu();
        cin>> choice;
    }

    cout<<"Good bye!\n";
    
    return 0;
}

string int_to_char(int& num){

    temp = "";
    temp2 = "";
    int j = 0;
    int r;

    do{
        r = num%10;
        num = num/10;
        temp += r + 0x30;
        ++j;
    }
    while(num != 0);

    for(int i = j - 1; i >= 0; i--)
        temp2 += temp[i];
    

    return temp2;
}

void main_menu(){

    cout<<"\n\n********* Main Menu *********\n"
        <<"1. Sign up\n"
        <<"2. Login\n"
        <<"3. Rank\n"
        <<"4. Challenge\n"
        <<"5. Exit\n\n"
        <<"Please enter your choice (5 to exit the game): ";
}

void signup(){

    string confirm_password;

    bool repeat = false;

    cout<<"\n\n********* Signup *********\n\n"
        <<"Username (* to go back): ";
    cin>> username;


    fstream user;
    user.open("user.txt");

    while (user >> temp && username != "*"){
        
        if(temp == username)
            repeat = true;
    }

    user.close();

    fstream newUser("user.txt", ios::app),
            newPass("password.txt", ios::app),
            newlavel("user-level.txt", ios::app),
            newMoney("money.txt", ios::app),
            newExtra("extra-word.txt", ios::app),
            newChance("chance.txt", ios::app),
            newAnswer("user-answer.txt", ios::app);

    if(repeat == false && username != "*"){

        cout<<"Creat a password: ";
        cin>> password;

        cout<<"Confirm password: ";
        cin>> confirm_password;

        while(password != confirm_password){

            cout<<"Password is not confirmed! Try again.\n";

            cout<<"Creat a password: ";
            cin>> password;

            cout<<"Confirm password: ";
            cin>> confirm_password;
        }
        if (last_line==0)
            {newUser << username; newPass << password; newlavel<< 1; newMoney<< 0; newExtra<< 0; newChance<< 0; newAnswer << ".";}            
        else
            {newUser <<endl<< username; newPass <<endl<< password; newlavel<<endl<< 1; newMoney<<endl<< 0; newExtra<<endl<< 0; newChance<<endl<< 0; newAnswer <<endl<<".";}
    }

    else if(username != "*"){

        cout<<"\n\nThis username is already exist!";
        signup();
    }

    newUser.close();
    newPass.close();
    newlavel.close();
    newMoney.close();
    newExtra.close();
    newChance.close();

    ++last_line;
}

void login(){

    line = 1;

    bool flag = false;

    cout<<"\n\n********* Login *********\n\n"
        <<"Username (* to go back): ";
    cin>> username;

    if(username != "*"){        
        cout<<"Enter the password (* to go back): ";
        cin>> password;
    }
            
    else if(username != "*" && password != "*"){

        fstream user("user.txt"),
                pass("password.txt"),
                userlevel("user-level.txt"),
                userMoney("money.txt"),
                userExtra("extra-word.txt"),
                userChance("chance.txt"),
                userAnswer("user-answer.txt");
        
        while(user >> temp){

            if(temp == username){
                flag = true;
                break;
            }
            ++line;
        }

        flag = false;

        while(pass >> temp){

            if(temp == password){
                flag = true;
                break;
            }
        }

        if(flag == true){

        
            for(int i=1; userlevel >> level; i++){

                if(i == line)
                    break;
            }
            
            for(int i=1; userMoney >> money; i++){

                if(i == line)
                    break;
            }

            for(int i=1; userExtra >> eWord; i++){

                if(i == line)
                    break;
            }

            for(int i=1; userChance >> chance; i++){

                if(i == line)
                    break;
            }

            for(int i=1; getline(userAnswer, allAnswers, '\n'); i++){

                if(i == line)
                    break;
            }


            user.close();
            pass.close();
            userlevel.close();
            userMoney.close();
            userExtra.close();
            userChance.close();
            userAnswer.close();



            cout<<"\n\nHello "<< username;

            //going to internal menu

            internal_menu();
            cin>> choice;

            while(choice != '5'){

                switch (choice){

                    case '1':
                        continue_game();
                        break;

                    case '2':
                        choose_level();
                        break;

                    case '3':
                        wheel_of_luck();
                        break;

                    case '4':
                        edit_profile();
                        break;

                    default:
                        cout<<"\n\nEntered Number is Wrong! Please Enter number between(1 - 5).\n\n";
                }

                internal_menu();
                cin>> choice;
                
            }

        }

        else{

            cout<<"\nUsername or password is wrong. Try again!";
            login();
        }

    }
}

void ranking(){

    bool sort = false;
    int size = 0;
    int rank_level[20];
    string name[20], n;

    fstream level("user-level.txt"),
            user("user.txt");

    for (int i = 0, j; level >> j; i++){
        
        rank_level[i] = j;
        ++size;
    }

    for (int i = 0; user >> n; i++)
        name[i] = n;

    for(int i = 0; i < size - 1; i++){
        sort = true;

        for(int j = size - 1, t; j > i; j--){

            if(rank_level[j] < rank_level[j-1]){

                t = rank_level[j];
                rank_level[j] = rank_level[j-1];
                rank_level[j-1] = t;

                temp = name[j];
                name[j] = name[j-1];
                name[j-1] = temp;

                sort = false;
            }
        }
    }

    cout<<"\n\n********* Rank *********\n\n"
        <<"User          Level\n\n";

    for(int i = size - 1, j = 1, x; i >= 0; i--, j++){

        x = 16 - name[i].size();

        cout<< j <<". "<< name[i] <<setw(x)<< rank_level[i] <<endl;
    }

    level.close();
    user.close();
    
    cout<<endl<<endl<<"Enter anything to go to the main menu: ";
    cin>> temp;
    
}

void challenge(){

    struct challenge_mode{

        string name;

        string answer;

        int point;
    };

    challenge_mode p1, p2;      // 2 players information

    int turn = 1;

    int maxPoint = 0;       //max point of the game

    string main;          //main : main words end with "."

    string letters;        //letters : letters of the game

    int num = 0;    //number of main words

    int random;

    srand(time(0));     //chooseing a random game

    random = rand()%17 + 1;

    fstream level("letters-of-levels.txt"), mainword("mainwords.txt");

    for(int i=1; getline(level, letters, '\n'); i++){

        if(i == random)
            break;
    }

    for(int i=1; getline(mainword, main, '\n'); i++){

        if(i == random)
            break;
    }

    //counting main words
    
    for(int i=0; main[i] != '.'; i++){

        if(main[i] == ' ')
            ++num;
    }

    for (int i = 0; main[i] != '\0'; i++){

        if(main[i] != ' ' && main[i] != '\n')
            ++maxPoint;
    }

    mainword.close();
    level.close();

    cout<<"\n\n********* Challenge *********\n\n"
        <<"\"If you enter * instead of answer, you'll lose.\"\n\n"
        <<"Enter the names:\n"
        <<"Player 1: ";

        cin>> p1.name;

        p1.point = 0;
        p2.point = 0;

        cout<<"Player 2: ";

        cin>> p2.name;

        p2.answer = "";
        p1.answer = "";


        while (true){

            cout<<"\n\nPlayer 1: "<<p1.name<<"  Score: "<<p1.point
                <<"\t\t"<<"Player 2: "<<p2.name<<"  Score: "<<p2.point<<endl;
            
            if(turn == 1){

                cout<<"\nTurn "<< p1.name <<endl<<endl<< letters <<"\n\n";
                challeng_answers1 += p1.answer + " ";

                cout<< p1.name <<" enter a word: ";
                cin>> p1.answer;
                cout<<endl;
                p1.point = challenge_turn_player1(p1.answer, main);
                turn = 2;
            }

            else{

                cout<<"\nTurn "<< p2.name <<endl<<endl<< letters<<"\n\n";

                challeng_answers2 += p2.answer + " ";

                cout<< p2.name <<" enter a word: ";
                cin>> p2.answer;
                cout<<endl;
                p2.point = challenge_turn_player2(p2.answer, main);
                turn = 1;
            }

            if (p1.answer == "*"){
                cout<<endl<< p2.name <<" wins!";
                break;
            }
            else if(p2.answer == "*"){
                cout<<endl<< p1.name <<" wins!";
                break;
            }

            if(p1.point == maxPoint && p2.point == maxPoint){
                cout<<endl<< "------- Draw -------";
                break;
            }

            else if (p1.point == maxPoint){
                cout<<endl<< p1.name <<" wins!";
                break;
            }

            else if (p2.point == maxPoint){
                cout<<endl<< p2.name <<" wins!";
                break;
            }
        }
        
}

int challenge_turn_player1(string answer, string main){

    flag = false;
    
    string str = "";

    bool correctAnswer = false;      //check if the answer is wrong

    for(int i = 0; main[i] != '\0'; i++){

        if(main[i] != ' ')
            str += main[i];

        else if(str == answer){
            correctAnswer = true;
            str = "";
            break;
        }
        else str = "";
    }

    if(correctAnswer == false && answer != "*")
        cout<<"\n----- Wrong answer -----\n\n";


    int point = 0;

    string word = "";

    challeng_answers1 += answer + " ";

    //the next loop searchs main words in challeng_answers string

    flag = false;
    for (int i = 0, l=0 ; main[i] != '\0' && answer != "*"; i++){

        flag = false;

        if(main[i] != ' ' && main[i] != '\n'){

            //it counts letters

            ++l;

            //assign a word in a temp string

            word += main[i];
        }

        else if(main[i] != '\n') {

            for(int i = 0; challeng_answers1[i] != '\0'; i++){

                if(challeng_answers1[i] != ' ')
                    temp += challeng_answers1[i];

                else {

                    //if the answer is available, it will be printed itself and bool flag will be true

                    if(temp == word){

                        temp = "";

                        cout<< word <<endl;

                        word = "";

                        flag = true;

                        point += l;

                        l = 0;
                        
                        break;
                    }

                    temp = "";
                }
            }

            // if the answer is not available, "-" will be printed in the number of letters specified by the variable l

            if(flag == false){

                for(int i=1; i<=l; i++)
                    cout<<"-";

                cout<<endl;

                word = "";

                temp = "";

                l = 0;
            }
        }
    }

    
    return point;
}

int challenge_turn_player2(string answer, string main){

    flag = false;

    string str = "";

    bool correctAnswer = false;      //check if answer is wrong

    for(int i = 0; main[i] != '\0'; i++){

        if(main[i] != ' ')
            str += main[i];

        else if(str == answer){
            correctAnswer = true;
            str = "";
            break;
        }
        else str = "";
    }

    if(correctAnswer == false && answer != "*")
        cout<<"\n----- Wrong answer -----\n\n";


    string word = "";

    int point = 0;

    challeng_answers2 += answer + " ";

    for (int i = 0, l=0 ; main[i] != '\0' && answer != "*"; i++){


        if(main[i] != ' ' && main[i] !='\n'){
            //count letters
            ++l;
            //assign a word in a temp string

            word += main[i];
        }

        else if(main[i] != '\n') {

            for(int i = 0; challeng_answers2[i] != '\0'; i++){

                if(challeng_answers2[i] != ' ')
                    temp2 += challeng_answers2[i];

                else {

                    if(temp2 == word){

                        temp2 = "";

                        cout<< word <<endl;

                        word = "";

                        flag = true;

                        point += l;

                        l = 0;

                        break;
                    }

                    temp2 = "";
                }
            }

            if(flag == false){

                for(int i=1; i<=l; i++)
                    cout<<"-";

                cout<<endl;

                word = "";

                temp2 = "";

                l = 0;
            }
        }
    }


    
    return point;
}

void internal_menu(){
    int current_level;

    if(level != "Final")
        current_level = stoi(level);

    if(current_level == 18)
        level = "Final";

    cout<<"\n\n********* Record *********\n\n"
        <<"level: "<< level
        <<"\nMoney: "<< money
        <<"\nExtra words: "<< eWord
        <<"\nChances: "<< chance;

    cout<<"\n\n********* Internal Menu *********\n"
    <<"1. Continue game\n"
    <<"2. Choose level\n"
    <<"3. Wheel of luck\n"
    <<"4. Edit profile\n"
    <<"5. Logout\n\n"
    <<"Please enter your choice (5 to logout): ";
}

void continue_game(){

    string letter;  //letters of game

    string main;        //mainwords of level

    string subword;     //subwords of level

    int added_coin = 0;     // coins wich player get by subwords

    struct Amirza{

        int num_of_extra_words,
            coin,
            current_level,
            current_season,
            added_chance;

        string answer = "";
    }
    player;
    

    player.answer = "";

    player.num_of_extra_words = stoi(eWord);

    player.coin = stoi(money);

    fstream current_level("user-level.txt");

    for(int i = 1; current_level >> level; i++)
        if(i == line)
            break;

    current_level.close();

    player.current_level = stoi(level);


    if(player.current_level <= 17){
    
        cout<<"\n\n********* Go on level " <<player.current_level<<" *********\n\n";

        //collecting letters, mainwords, subwords and previous answers
        
        fstream letters_of_level("letters-of-levels.txt"), mainwords_of_level("mainwords.txt"), subwords_of_level("subwords.txt"),
                previous_answers("user-answer.txt");

        for(int i = 1; letters_of_level >> letter; i++)
            if(i == player.current_level)
                break;

        for(int i = 1; getline(mainwords_of_level, main, '\n'); i++)
            if(i == player.current_level)
                break;

        for(int i = 1; getline(subwords_of_level, subword, '\n'); i++)
            if(i == player.current_level)
                break;

        for(int i = 1; getline(previous_answers, allAnswers, '\n'); i++)
            if(i == line)
                break;

        
        letters_of_level.close();
        mainwords_of_level.close();
        subwords_of_level.close();
        previous_answers.close();



        if(1 <= player.current_level && player.current_level <= 4)
            player.current_season = 1;

        else if(5 <= player.current_level && player.current_level <= 11)
            player.current_season = 2;

        else if(12 <= player.current_level && player.current_level <= 17)
            player.current_season = 3;

        cout<< "\nSeason: "<< player.current_season <<"\tLevel: " << player.current_level << "\tCoin: " << player.coin + added_coin << "\t\tExtra words: " << player.num_of_extra_words <<endl;

        int first_extra = player.num_of_extra_words;
        int show_extra = player.num_of_extra_words;
        int whole_coins;
        int num_of_mainwords = 0;   // these variables count number of words. If they are tied, the game is over
        int num_of_answers = 0;


        while(player.answer != "*"){

            cout<<endl<< letter <<endl<<endl;
                    
            show_current_game_map(main, subword, player.answer);

            //the next function searchs subwords in allAnswers string

            show_extra = search_subwords(subword, player.answer, added_coin, first_extra);

            player.num_of_extra_words = show_extra;


            // if number of extra words is more than 6, the programm will show 6 less

            while(show_extra >= 6)
                show_extra -= 6;

            if(player.answer == "#" && player.coin + added_coin >= 80){
                help = true;
                player.coin -= 80;
            }

            else if(player.answer == "#")
                cout<<"\nSorry, you don't have enough coin. You need "<<80 - (player.coin + added_coin)<<" more.\n";

            
            // if player enter "$", letters will be reorded

            if(player.answer == "$")
                shuffle(letter);
            
            

            //check if player has entered all of the mainwords and finnished the level


            for (int i = 0; main[i] != '\0'; i++){

                if(main[i] != ' ' && main[i] != '\n'){
                    //collecting a main word in a word string
                    temp2 += main[i];

                    if (main[i + 1] == ' ' || main[i + 1] == '\n')
                        ++num_of_mainwords;
                }

                else{

                    for(int i = 0; allAnswers[i] != '\0'; i++){

                        if(allAnswers[i] != '.')
                            temp += allAnswers[i];

                        else {

                            if(temp == temp2){
                                ++num_of_answers;
                            }
                            
                            temp = "";
                        }
                    }

                    temp2 = "";
                }
            }

            if(num_of_answers == num_of_mainwords){

                cout<<"\n\n***************** Congratulations, you finnished level "<< level <<" *****************"<<endl;
                ++player.current_level;
                player.coin += 100;
                break;
            }
            else{
                num_of_mainwords = 0;
                num_of_answers = 0;
            }

            cout<< "\nSeason: "<< player.current_season <<"\tLevel: " << player.current_level << "\tCoin: " << player.coin + added_coin << "\t\tExtra words: " << show_extra <<endl;

        }

        //if player win the game, programm will store all informain in files

        if(player.answer != "*"){

            if(player.current_level == 5 || (player.current_level == 12 || player.current_level == 18)){

                player.added_chance = stoi(chance);

                ++player.added_chance;

                chance = int_to_char(player.added_chance);

                fstream update_chance("chance.txt"), chancetemp("chancetemp.txt", ios::out);
                chancetemp.open("chancetemp.txt");
                chancetemp.close();

                fstream temp_chance("chancetemp.txt");

                for(int i = 1; update_chance >> temp; i++){
            
                    if(i == line)
                        temp_chance << chance;
                    else
                        temp_chance << temp;

                    if(i != last_line)
                        temp_chance<<endl;
                }

                update_chance.close();
                temp_chance.close();

                remove("chance.txt");
                rename("chancetemp.txt", "chance.txt");
            }
            
            allAnswers = ".";
            whole_coins = player.coin + added_coin;
            save_info(whole_coins, player.num_of_extra_words, player.current_level, allAnswers);
            continue_game();
        }

        else {
        
            whole_coins = player.coin + added_coin;

            save_info(whole_coins, player.num_of_extra_words, player.current_level, allAnswers);
        }
    }

    else
        cout<<"\n****** You've already finnished the game. Go to \"choose level\" and play previous levels ******\n";

}

void choose_level(){

    bool finnished_game = false;

    struct choosing_level{

        int choosen_level,
            coin,
            season;
        string answer;
    }
    player;
    
    string main;    //mainwords of the level

    string letter;

    int max_level;

    if(level == "Final"){
        max_level = 17;
        finnished_game = true;
    }

    else
        max_level = stoi(level);

    player.coin = stoi(money);
    
    cout<<"\n\n********* Choose level *********\n\n"
        <<"Pay attention:\n* Extra words won't be counted.\n* You won't get any coin if you finnish the previous levels successfully.\n* If you choose the last level can be choosen, extra words, chances and coins will be stored.\n* If you want help during the game, regardless of whether you chose the last level or not, 80 coins will be deducted."
        <<"\n\nChoose a level from 1 to " << max_level <<" (-1 to go back to the menu): ";

    cin >> player.choosen_level;

    while(!(1 <= player.choosen_level && player.choosen_level <= max_level)  && player.choosen_level != -1){

        cout<<"You are not allowed to play level "<< player.choosen_level << ". Choose a level from 1 to " << max_level <<" (-1 to go back to the menu): ";
        cin >> player.choosen_level;
    }


    if((player.choosen_level == max_level) && finnished_game == false)
        continue_game();


    else if(player.choosen_level != -1){

        if(1 <= player.choosen_level && player.choosen_level <= 4)
            player.season = 1;

        else if(5 <= player.choosen_level && player.choosen_level <= 11)
            player.season = 2;

        else if(12 <= player.choosen_level && player.choosen_level <= 17)
            player.season = 3;

        cout<< "\nSeason: "<< player.season <<"\tLevel: " << player.choosen_level << "\tCoin: " << player.coin <<endl;


        fstream mainFile("mainwords.txt"), letterFile("letters-of-levels.txt");

        for(int i = 1; getline(mainFile, main, '\n'); i++)
            if(i == player.choosen_level)
                break;

        for(int i = 1; getline(letterFile, letter, '\n'); i++)
            if(i == player.choosen_level)
                break;


        mainFile.close();
        letterFile.close();


        string str = "choose_level function";


        while(player.answer != "*"){

            cout<<endl<< letter <<endl<<endl;
                    
            show_current_game_map(main, str, player.answer);


            if(player.answer == "#" && player.coin >= 80){
                help = true;
                player.coin -= 80;
            }

            else if(player.answer == "#")
                cout<<"\nSorry, you don't have enough coin. You need "<< 80 - player.coin <<" more.\n";

            
            // if player enter "$", letters will be reorded

            if(player.answer == "$")
                shuffle(letter);
            
            
            //check if player has entered all of the mainwords and finnished the level

            int num_of_mainwords = 0;   // these variables count number of words. If they are tied, the game is over
            int num_of_answers = 0;

            for (int i = 0; main[i] != '\0'; i++){

                if(main[i] != ' ' && main[i] != '\n'){
                    //collecting a main word in a word string
                    temp2 += main[i];

                    if (main[i + 1] == ' ' || main[i + 1] == '\n')
                        ++num_of_mainwords;
                }

                else{

                    for(int i = 0; allAnswers[i] != '\0'; i++){

                        if(allAnswers[i] != '.')
                            temp += allAnswers[i];

                        else {

                            if(temp == temp2){
                                ++num_of_answers;
                            }
                            
                            temp = "";
                        }
                    }

                    temp2 = "";
                }
            }

            
            if(num_of_answers == num_of_mainwords){

                cout<<"\n\n***************** Congratulations, you finnished level "<< player.choosen_level <<" *****************"<<endl;
                break;
            }

            cout<< "\nSeason: "<< player.season <<"\tLevel: " << player.choosen_level << "\tCoin: " << player.coin <<endl;

        }


        money = int_to_char(player.coin);


        fstream moneyFile("money.txt"), moneytemp("moneytemp.txt", ios::out);
        moneytemp.open("moneytemp.txt");
        moneytemp.close();

        fstream money_temp("moneytemp.txt");

        for(int i = 1; moneyFile >> temp; i++){

            if(i == line){
                money_temp<< money;
            }

            else
                money_temp << temp;
            
            if(i != last_line)
                money_temp<<endl;
        }

        moneyFile.close();
        money_temp.close();

        remove("money.txt");
        rename("moneytemp.txt", "money.txt");

    }

}

void show_current_game_map(string &main, string &sub, string &answer){

    flag = false;
    
    string str = "";

    bool correctAnswer = false;
    
    //check if the answer is wrong

    for(int i = 0; main[i] != '\0'; i++){

        if(main[i] != ' ')
            str += main[i];

        else if(str == answer){
            correctAnswer = true;
            str = "";
            break;
        }
        else str = "";
    }

    for(int i = 0; sub[i] != '\0' && sub != "choose_level function"; i++){

        if(sub[i] != ' ')
            str += sub[i];

        else if(str == answer){
            correctAnswer = true;
            str = "";
            break;
        }
        else str = "";

    }



    if(correctAnswer == false && (answer != "" && (answer != "#" && answer != "$")))
        cout<<"----- Wrong answer -----\n\n";



    string word = "";

    //the next loop searchs main words in allAnswers string

    for (int i = 0, l=0 ; main[i] != '\0'; i++){

        flag = false;

        if(main[i] != ' '){

            //it counts letters of a main word

            ++l;

            //collecting a main word in a word string

            word += main[i];
        }

        else if(main[i] != '\n') {

            for(int i = 0; allAnswers[i] != '\0'; i++){

                if(allAnswers[i] != '.')
                    temp += allAnswers[i];

                else {

                    //if the answer is available, it will be printed itself and bool flag will be true

                    if(temp == word){

                        temp = "";

                        cout<< word <<endl;

                        word = "";

                        flag = true;

                        l = 0;
                        
                        break;
                    }

                    temp = "";
                }
            }

            // if the answer is  unavailable, "-" will be printed in the number of letters specified by the variable "l"

            if(flag == false){

                if(help == true){

                    cout<< word[0];
                    --l;
                    help = false;
                }

                for(int i=1; i<=l; i++)
                    cout<<"-";

                cout<<endl;

                word = "";

                temp = "";

                l = 0;
            }
        }
    }



    cout<<"\nIf you want to go back to internal menu enter * :\n"
        <<"If you want another order of letters enter $ :\n"
        <<"If you need help enter # :\n\n"
        <<"Enter a word: ";
    cin >> answer;
    allAnswers += answer + ".";
}

int search_subwords(string &sub, string &answer, int &added_coin, int &f_extra){

    int extra = 0;

    string word = "";

    for (int i = 0 ; sub[i] != '\0'; i++){

        //collecting a subword in word string

        if(sub[i] != ' ')
            word += sub[i];
        

        else if(sub[i] != '\n') {

            for(int i = 0; allAnswers[i] != '\0'; i++){

                if(allAnswers[i] != '.')
                    temp += allAnswers[i];

                else {

                    if(temp == word){
                        
                        if(word == answer)
                            cout<<"\nIt was an extra word!\n";

                        temp = "";

                        word = "";

                        extra++;

                        break;
                    }

                    temp = "";
                }
            }
        }
    }

    extra += f_extra;

    added_coin = add_coin_by_subwords(extra);

    return extra;
}

int add_coin_by_subwords(int &extra){

    int x, coin;
    
    x = extra / 6;

    coin = x * 50;

    return coin;
}

void wheel_of_luck(){

    int userChance = stoi(chance);

    int userMoney = stoi(money);
    
    cout<<"\n\n********* Wheel of luck *********\n\n"
        <<"1. 50 coins      possibility: 30%\n"
        <<"2. 70 coins      possibility: 20%\n"
        <<"3. 90 coins      possibility: 20%\n"
        <<"4. 110 coins     possibility: 15%\n"
        <<"5. 150 coins     possibility: 10%\n"
        <<"6. 220 coins     possibility: 5%\n\n";


    srand(time(0));

    int random = rand()%100 + 1;

    if(userChance != 0){
        if(1 <= random && random <= 5){
            cout<<"You won 220 coins.\n";
            userMoney += 220;
        }

        else if(6 <= random && random <= 15){
            cout<<"You won 150 coins.\n";
            userMoney += 150;
        }

        else if(16 <= random && random <= 30){
            cout<<"You won 110 coins.\n";
            userMoney += 110;
        }

        else if(31 <= random && random <= 50){
            cout<<"You won 90 coins.\n";
            userMoney += 90;
        }

        else if(51 <= random && random <= 70){
            cout<<"You won 70 coins.\n";
            userMoney += 70;
        }

        else if(71 <= random && random <= 100){
            cout<<"You won 50 coins.\n";
            userMoney += 50;
        }

        //following function will convert int variables to char

        money = int_to_char(userMoney);

        --userChance;   //now user have one less chance

        chance = int_to_char(userChance);
        
        //rewriting files with new money and chance info
        //starts with money

        fstream moneyFile("money.txt"), moneytemp("moneytemp.txt", ios::out);
        moneytemp.open("moneytemp.txt");
        moneytemp.close();

        fstream money_temp("moneytemp.txt");

        for(int i = 1; moneyFile >> temp; i++){

            if(i == line){
                money_temp<< money;
            }

            else
                money_temp << temp;
            
            if(i != last_line)
                money_temp<<endl;
        }

        moneyFile.close();
        money_temp.close();

        remove("money.txt");
        rename("moneytemp.txt", "money.txt");


        //rewritnig chance file

        fstream chanceFile("chance.txt"), chancetemp("chancetemp.txt", ios::out);

        chancetemp.open("chancetemp.txt");
        chancetemp.close();

        fstream chance_temp("chancetemp.txt");

        for(int i = 1; chanceFile >> temp; i++){

            if(i == line){
                chance_temp<< chance;
            }

            else
                chance_temp << temp;
            
            if(i != last_line)
                chance_temp<<endl;
        }

        chanceFile.close();
        chance_temp.close();

        remove("chance.txt");
        rename("chancetemp.txt", "chance.txt");

    }

    else
        cout<<"Sorry, you don't have a chance. Finish a season to get a chance.\n";



}

void edit_profile(){

    string newUsername, newPassword;

    cout<<"\n\n********* Edit profile *********\n\n"<<"Hi "<< username <<endl;

    cout<<"\nCreat a new username (* to return): ";
    cin>> newUsername;
    
    if(newUsername != "*"){


        while(true){

            cout<<"\n\nCreat a new password: ";
            cin>> newPassword;

            cout<<"Confirm your new password: ";
            cin>> temp;

            if(temp != newPassword)
                cout<<"\n\nPassword isn't confirmed! Try again.";
            else
                break;
        }



        fstream  user("user.txt") ,pass("password.txt"), usertemp("usertemp.txt", ios::out), passtemp("passwordtemp.txt", ios::out);

        usertemp.open("usertemp.txt");
        passtemp.open("passwordtemp.txt");
        passtemp.close();
        usertemp.close();

        fstream tempuser("usertemp.txt"), tempPass("passwordtemp.txt");

        for(int i = 1 ;user >> temp; i++){

            if(temp == username){
                username = newUsername;
                tempuser<< username;
            }

            else
                tempuser<< temp;

            if(i != last_line)
                tempuser <<endl;
        }


        for(int i = 1; pass >> temp; i++){

            if(temp == password && i == line){
                password = newPassword;
                tempPass << password;
            }

            else
                tempPass << temp;

            if(i != last_line)
                tempPass <<endl;
        }

        tempuser.close();
        user.close();
        pass.close();
        tempPass.close();

        remove("password.txt");
        remove("user.txt");
        rename("passwordtemp.txt", "password.txt");
        rename("usertemp.txt", "user.txt");


        cout<<"\n************ Profile is edited successfully ************\n\n";
    }
}

void save_info(int user_money, int user_num_of_extra, int newLevel, string &user_answers){
    
    money = int_to_char(user_money);
    eWord = int_to_char(user_num_of_extra);
    level = int_to_char(newLevel);


    fstream answer_file("user-answer.txt"), temp_answer("answertemp.txt", ios::out);
    temp_answer.open("answertemp.txt");
    temp_answer.close();

    fstream answer_temp("answertemp.txt");

    for(int i = 1; answer_file >> temp; i++){
        
        if(i == line)
            answer_temp << user_answers;
        else
            answer_temp << temp;
        
        if(i != last_line)
            answer_temp<<endl;
    }

    answer_file.close();
    answer_temp.close();

    remove("user-answer.txt");
    rename("answertemp.txt", "user-answer.txt");


    fstream money_file("money.txt"), temp_money("moneytemp.txt", ios::out);
    temp_money.open("moneytemp.txt");
    temp_money.close();

    fstream money_temp("moneytemp.txt");


    for(int i = 1; money_file >> temp; i++){
        
        if(i == line)
            money_temp << money;
        else
            money_temp << temp;
        
        if(i != last_line)
            money_temp<<endl;
    }

    money_file.close();
    money_temp.close();

    remove("money.txt");
    rename("moneytemp.txt", "money.txt");


    fstream extra_file("extra-word.txt"), temp_extra("extratemp.txt", ios::out);
    temp_extra.open("extratemp.txt");
    temp_extra.close();

    fstream extra_temp("extratemp.txt");


    for(int i = 1; extra_file >> temp; i++){
        
        if(i == line)
            extra_temp << eWord;
        else
            extra_temp << temp;
        
        if(i != last_line)
            extra_temp<<endl;
    }

    extra_file.close();
    extra_temp.close();

    remove("extra-word.txt");
    rename("extratemp.txt", "extra-word.txt");

    fstream level_file("user-level.txt"), temp_level("user-level-temp.txt", ios::out);
    temp_level.open("user-level-temp.txt");
    temp_level.close();

    fstream level_temp("user-level-temp.txt");


    for(int i = 1; level_file >> temp; i++){
        
        if(i == line)
            level_temp << level;
        else
            level_temp << temp;
        
        if(i != last_line)
            level_temp<<endl;
    }

    level_file.close();
    level_temp.close();

    remove("user-level.txt");
    rename("user-level-temp.txt", "user-level.txt");


    cout<<"\n\n-------------- Saved --------------\n\n";

    if(newLevel > 17)
        cout<<"*********** You have finnished the game! ***********\n\n";
}

void shuffle(string &shuffled_letters){

  int size = shuffled_letters.length();

  string shuffle = "";

  char x;


  bool flag = true;

  srand(time(0));

    for(int i=0;i<100;i++)
        shuffle += shuffled_letters[rand() % size];



    shuffled_letters = "";

    int j = 0;

    for(int i = 0; i < 100; i++){

        flag = true;

        x = shuffle[i];

        while( j<i){

            if(x == shuffle[j] && flag == true){
                flag = false;
                break;
            }
            j++;
        }

        if(flag == true)
            shuffled_letters += x;

        j = 0;
    }
}