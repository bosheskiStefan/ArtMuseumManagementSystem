#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

class Art
{
protected:
        string name;
        string artist;
        int timeTook;
        vector <int> ratings;
public:
    Art (){}
    Art(string name, string artist, int timeTook, vector <int> ratings)
    {
        this->name=name;
        this->artist=artist;
        this->timeTook=timeTook;
        this->ratings=ratings;
    }
    virtual void print()
    {
        cout<<"Name of the painting: "<<name<<endl<<"Artist: "<<artist<<endl<<"Time :"<<timeTook<<endl<<"Rating: "<<averageRatings()<<"costs: "<<price()<<endl;
    }
    virtual float price() =0;
    float averageRatings()
    {
        int r=0;
        vector <int>:: iterator i;
        for(i=ratings.begin(); i!=ratings.end(); i++)
        {
            r+=(*i);
        }
        return r/ratings.size();
    }
    string getName()
    {
        return name;
    }
    string getArtist()
    {
        return artist;
    }
    int getTimeTook()
    {
        return timeTook;
    }
    vector <int> getRatings()
    {
        return ratings;
    }
    virtual ~ Art (){};
};

class Painting : public Art
{
private:
    string technique;
    int usedColors;
    float canvasSize;
public:
    Painting(): Art (){}
    Painting(string name, string artist, int timeTook, vector <int> ratings, string technique, int usedColors, float canvasSize): Art(name, artist, timeTook, ratings)
    {
        this->technique=technique;
        this->usedColors=usedColors;
        this->canvasSize=canvasSize;
    }
    void print()
    {
        cout<<"The technique used is "<<technique<<" with "<<usedColors<<" colors, on a size "<<canvasSize<<" canvas."<<endl;
        Art::print();
    }
    float price()
    {
        return timeTook*canvasSize*averageRatings();
    }
    float getCanvas()
    {
        return canvasSize;
    }
    int getColors()
    {
        return usedColors;
    }
};

class Sculpture : public Art
{
private:
    string material;
    float height;
    float weight;
public:
    Sculpture():Art(){}
    Sculpture(string name, string artist, int timeTook, vector <int> ratings, string material, float height, float weight):Art(name,artist,timeTook,ratings)
    {
        this->material=material;
        this->height=height;
        this->weight=weight;
    }
    void print()
    {
        cout<<"The sculpture is made of "<<material<<" is "<<height<<" tall and weighs "<<weight<<endl;
        Art::print();
    }
    float price()
    {
        return timeTook*height*averageRatings();
    }
    float getHeight()
    {
        return height;
    }
    float getWeight()
    {
        return weight;
    }
};

class Museum
{
private:
    vector<Art*> artifacts;
public:
    Museum(){}
    Museum(vector <Art*> artifacts)
    {
        this->artifacts=artifacts;
    }
    Museum &operator+=(Art *A)
    {
        artifacts.push_back(A);
        return *this;
    }
    Museum &operator-=(string ar)
    {
        int temp=0;
        vector<Art*>::iterator i;
        for(i=artifacts.begin(); i!=artifacts.end();)
        {
            if((*i)->getArtist()==ar)
            {
                artifacts.erase(artifacts.begin()+temp);
            }
            else
            {
                i++;
                temp++;
            }
        }
        return *this;
    }
    void totalPrice()
    {
        int sum=0, cnt=0;
        vector<Art*>::iterator i;
        for(i=artifacts.begin(); i!=artifacts.end(); i++)
        {
            Painting *P=dynamic_cast<Painting*>(*i);
            Sculpture *S=dynamic_cast<Sculpture*>(*i);
            if(P!=nullptr)
            {
                sum+=(*i)->price();
            }
            if(S!=nullptr)
            {
                cnt+=(*i)->price();
            }
        }
        cout<<"The total price for the paintings is: "<<sum<<endl;
        cout<<"The total price for the sculptures is: "<<cnt<<endl;
    }
    void totalRatings()
    {
        int sum=0, cnt=0;
        vector<Art*>::iterator i;
        for(i=artifacts.begin(); i!=artifacts.end(); i++)
        {
            sum+=(*i)->averageRatings();
            vector <int> rat= (*i)->getRatings();
            vector <int>:: iterator it;
           for(it=rat.begin(); it!=rat.end(); it++)
           {
               cnt+=(*it);
           }
        }
        cout<<"The number of ratings is "<<cnt<<endl;
        cout<<"Avg of avg "<<sum/artifacts.size();
    }
    void countArtist(string art)
    {
       int sum=0, cnt=0;
        vector<Art*>::iterator i;
        for(i=artifacts.begin(); i!=artifacts.end(); i++)
        {
            Painting *P=dynamic_cast<Painting*>(*i);
            Sculpture *S=dynamic_cast<Sculpture*>(*i);
            if(P!=nullptr)
            {
                if(P->getArtist()==art)
                {
                  sum++;
                }

            }
            if(S!=nullptr)
            {
               if(S->getArtist()==art)
                {
                  cnt++;
                }
            }
        }
        cout<<"The number of paintings is: "<<sum<<" sculp: "<<cnt<<endl;
    }
    void checkTime(int t)
    {
        int sum=0, cnt=0;
        vector<Art*>::iterator i;
        for(i=artifacts.begin(); i!=artifacts.end(); i++)
        {
          if((*i)->getTimeTook()<=t)
          {
              sum++;
          }
          else
          {
              cnt++;
          }
        }
        cout<<"The ones more "<<sum<<"less "<<cnt<<endl;
    }
    void totalColors()
    {
        int sum=0;
        vector<Art*>::iterator i;
        for(i=artifacts.begin(); i!=artifacts.end(); i++)
        {
            Painting *P=dynamic_cast<Painting*>(*i);
            if(P!=nullptr)
            {
                sum+=P->getColors();
            }
        }
        cout<<"Num of col: "<<sum<<endl;
    }
    void biggestCanvas()
    {
        float temp=0;
        vector<Art*>::iterator i;
        for(i=artifacts.begin(); i!=artifacts.end(); i++)
        {
            Painting *P=dynamic_cast<Painting*>(*i);
            if(P!=nullptr)
            {
               if(P->getCanvas()>temp)
                {
                    temp=P->getCanvas();
                }
            }
        }
        cout<<"Biggest canvas dimens is "<<temp<<endl;
    }
    void shortestHeight()
    {
      float temp=9999999;
        vector<Art*>::iterator i;
        for(i=artifacts.begin(); i!=artifacts.end(); i++)
        {
            Sculpture *S=dynamic_cast<Sculpture*>(*i);
            if(S!=nullptr)
            {
               if(S->getHeight()<temp)
                {
                    temp=S->getHeight();
                }
            }
        }
        cout<<"Biggest sculpt is tall: "<<temp<<endl;
    }
    void totalWeight()
    {
        int temp=0;
        vector<Art*>::iterator i;
        for(i=artifacts.begin(); i!=artifacts.end(); i++)
        {
            Sculpture *S=dynamic_cast<Sculpture*>(*i);
            if(S!=nullptr)
            {
               temp+=S->getWeight();
            }
        }
        cout<<"Total weight of all sculpt: "<<temp<<endl;
    }
    void print()
    {
       vector<Art*>::iterator i;
       for(i=artifacts.begin(); i!=artifacts.end(); i++)
       {
           (*i)->print();
       }
    }
};
int main()
{
    class Museum M;
    int choice;
    do
    {
        cout << "1. Add an Artifact to the Exhibition." << endl;
        cout << "2. Eliminate an Artist." << endl;
        cout << "3. Display the Exhibition." << endl;
        cout << "4. Total Price of the Exhibition." << endl;
        cout << "5. The Ratings of the Exhibition." << endl;
        cout << "6. Count the amount of Art by an Artist." << endl;
        cout << "7. Check Time less and more than the input." << endl;
        cout << "8. Count the total Colors used." << endl;
        cout << "9. Show the biggest Canvas." << endl;
        cout << "10. Show the shortest Statue." << endl;
        cout << "11. Sum the weight of all the Statues." << endl;
        cout << "0. Exit." << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            {
                string name, artist, technique, material;
                int type, time, colors, num, i, r;
                float canvas, height, weight;
                vector <int> ratings;
                cout << "Do you want to add a Painting (1) or a Sculpture (2)?" << endl;
                cin >> type;
                if (type==1)
                {
                    cout << "Enter the name of the painting." << endl;
                    cin >> name;
                    cout << "Enter the name of the artist." << endl;
                    cin >> artist;
                    cout << "Enter the time it took to create the piece." << endl;
                    cin >> time;
                    cout << "Enter the number or ratings the piece has." << endl;
                    cin >> num;
                    for(i=0; i<num; i++)
                    {
                        cout << "Enter the " << i+1 << "-th rating." << endl;
                        cin >> r;
                        ratings.push_back(r);
                    }
                    cout << "Enter the technique used." << endl;
                    cin >> technique;
                    cout << "Enter the number of colors used." << endl;
                    cin >> colors;
                    cout << "Enter the canvas dimensions." << endl;
                    cin >> canvas;
                    Art *A = new Painting(name, artist, time, ratings, technique, colors, canvas);
                    M+=A;
                }
                if(type==2)
                {
                    cout << "Enter the name of the sculpture." << endl;
                    cin >> name;
                    cout << "Enter the name of the artist." << endl;
                    cin >> artist;
                    cout << "Enter the time it took to create the piece." << endl;
                    cin >> time;
                    cout << "Enter the number or ratings the piece has." << endl;
                    cin >> num;
                    for(i=0; i<num; i++)
                    {
                        cout << "Enter the " << i+1 << "-th rating." << endl;
                        cin >> r;
                        ratings.push_back(r);
                    }
                    cout << "Enter the material used." << endl;
                    cin >> material;
                    cout << "Enter the height of the piece." << endl;
                    cin >> height;
                    cout << "Enter the weight of the piece." << endl;
                    cin >> weight;
                    Art *A = new Sculpture(name, artist, time, ratings, material, height, weight);
                    M+=A;
                }
                break;
            }
        case 2:
            {
                string eleminate;
                cout << "Enter the artist you want to eliminate." << endl;
                cin >> eleminate;
                M-=eleminate;
                break;
            }
        case 3:
            {
                M.print();
                break;
            }
        case 4:
            {
                M.totalPrice();
                break;
            }
        case 5:
            {
                M.totalRatings();
                break;
            }
        case 6:
            {
                string coutArt;
                cout << "Enter the name of the artist you want to count." << endl;
                cin >> coutArt;
                M.countArtist(coutArt);
                break;
            }
        case 7:
            {
                int check;
                cout << "Enter the time you want to check each piece." << endl;
                cin >> check;
                M.checkTime(check);
                break;
            }
        case 8:
            {
                M.totalColors();
                break;
            }
        case 9:
            {
                M.biggestCanvas();
                break;
            }
        case 10:
            {
                M.shortestHeight();
                break;
            }
        case 11:
            {
                M.totalWeight();
                break;
            }
        case 0:
            {
                cout << "Exiting." << endl;
                break;
            }
        default:
            {
                cout << "Wrong input." << endl;
                break;
            }
        }
    }
    while (choice!=0);
    return 0;
}
