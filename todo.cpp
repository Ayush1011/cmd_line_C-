#include <bits/stdc++.h>
using namespace std;

void alignitem()
{
    fstream myfile("todo.txt");
    string line;
    vector<string> v;
    while (getline(myfile, line))
    {

        if (!line.empty())
        {
            v.push_back(line);
        }
    }
    myfile.close();
    myfile.open("todo.txt", ios::out | ios::trunc);

    for (int i = 0; i < v.size(); i++)
    {
        myfile << v[i] << endl;
    }
}

int main(int argc, char *argv[])
{
    //if input is only ./todo
    if (argc <= 1)
    {
        

        

        cout << "Usage :-" << endl;
        cout << "$ ./todo add \"todo item\"  # Add a new todo" << endl;
        cout << "$ ./todo ls               # Show remaining todos" << endl;
        cout << "$ ./todo del NUMBER       # Delete a todo" << endl;
        cout << "$ ./todo done NUMBER      # Complete a todo" << endl;
        cout << "$ ./todo help             # Show usage" << endl;
        cout << "$ ./todo report           # Statistics" << endl;

        
    }
    // input for ./todo help
    else
    {

        string s = argv[1];
        if (s == "help")
        {
            cout << "Usage :-" << endl;
            cout << "$ ./todo add \"todo item\"  # Add a new todo" << endl;
            cout << "$ ./todo ls               # Show remaining todos" << endl;
            cout << "$ ./todo del NUMBER       # Delete a todo" << endl;
            cout << "$ ./todo done NUMBER      # Complete a todo" << endl;
            cout << "$ ./todo help             # Show usage" << endl;
            cout << "$ ./todo report           # Statistics" << endl;
        }
        // input for ./todo add
        else if (s == "add")
        {
            string addedTodo = "";

            for (int i = 2; i < 100; i++)
            {
                if (argv[i] == NULL)
                {
                    break;
                }
                addedTodo += argv[i];
                addedTodo += " ";
            }

            if (addedTodo.empty())
            {
                cout << "Error: Missing todo string. Nothing added!" << endl;
                return 0;
            }

            ofstream outfile;
            outfile.open("todo.txt", std::ios_base::app);

            addedTodo = addedTodo.substr(0, addedTodo.size() - 1);

            outfile << addedTodo << endl;
            cout << "Added todo: \"" << addedTodo << "\"" << endl;

            outfile.close();
        }
        else if (s == "ls")
        {
            string line;
            vector<string> v;
            fstream myfile("todo.txt");
            ofstream fin("temp.txt", ofstream::out);

            myfile.clear();
            myfile.seekg(0);

            while (getline(myfile, line))
            {

                if (!line.empty())
                {
                    v.push_back(line);
                }
            }

            if (v.size() <= 0)
            {
                cout << "There are no pending todos!" << endl;
                return 0;
            }

            myfile.close();
            myfile.open("todo.txt", ios::out | ios::trunc);

            for (int i = 0; i < v.size(); i++)
            {
                myfile << v[i] << endl;
            }

            reverse(v.begin(), v.end());
            int p = v.size();
            for (int i = 0; i < v.size(); i++)
            {
                cout << "[" << p-- << "]"
                     << " " << v[i] << endl;
            }
            myfile.clear();
            myfile.seekg(0);
        }
        else if (s == "del")
        {

             fstream myfile("todo.txt");
             string line;
             int total=0;
            while (getline(myfile, line))
            {

                if (!line.empty())
                {
                    total++;
                }
            }

           




            if (argv[2] == NULL)
            {
                cout << "Error: Missing NUMBER for deleting todo." << endl;
                return 0;
            }
            string index = argv[2];





            int finalindex = stoi(index);

            if(finalindex>total){
               cout << "Error: todo #" << finalindex << " does not exist. Nothing deleted." << endl;

                return 0;
            }




           

            myfile.clear();
            myfile.seekg(0);

            ofstream ofs;
            ofs.open("temp.txt", ofstream::out);

            alignitem();

            // loop getting single characters
            myfile.clear();
            myfile.seekg(0);
            char c;
            int line_no = 1;
            bool istrue = false;
            
            while (myfile.get(c))
            {
                // if a newline character

                if (c == '\n')
                {
                    line_no++;
                    myfile << "\n";
                }

                // file content not to be deleted
                if (line_no != finalindex)
                {
                    ofs << c;
                }
                else
                {
                    istrue = true;
                }
            }

            if (istrue == false)
            {
                cout << "Error: todo #" << finalindex << " does not exist. Nothing deleted." << endl;

                return 0;
            }

            // closing output file
            ofs.close();

            // closing input file

            // remove the original file
            remove("todo.txt");

            // rename the file
            rename("temp.txt", "todo.txt");

            cout << "Deleted todo #" << finalindex << endl;

            myfile.close();
        }
        else if (s == "done")
        {
            if (argv[2] == NULL)
            {
                cout << "Error: Missing NUMBER for marking todo as done." << endl;
                return 0;
            }
            string index = argv[2];
            int finalindex = stoi(index);

            string line;

            fstream myfile("todo.txt");
            fstream ofs;
            ofs.open("done.txt", ios::app);
            fstream temp;
            temp.open("temp.txt", ofstream::out);

            myfile.clear();
            myfile.seekg(0);
            alignitem();

            // loop getting single characters
            char c;
            int line_no = 1;
            bool istrue = false;

            while (myfile.get(c))
            {
                // if a newline character

                if (c == '\n')
                {
                    line_no++;
                }

                if (line_no == finalindex)
                {
                    istrue = true;
                    ofs << c;
                }
                else
                {
                    temp << c;
                }
            }

            // ofs.clear();
            // ofs.seekg(0);

            if (istrue == false)
            {
                cout << "Error: todo #" << finalindex << " does not exist." << endl;
            }

            myfile.close();
            ofs.close();

            // closing input file

            // remove the original file
            remove("todo.txt");

            // rename the file
            rename("temp.txt", "todo.txt");
            cout << "Marked todo #" << finalindex << " as done." << endl;
        }
        else if (s == "report")
        {

            fstream myfile("todo.txt");
            fstream myfile1("done.txt");

            std::time_t rawtime;
            std::tm *timeinfo;
            char buffer[80];

            std::time(&rawtime);
            timeinfo = std::localtime(&rawtime);

            std::strftime(buffer, 80, "%Y-%m-%d", timeinfo);
            cout << buffer;

            int pending = 0;
            int completed = 0;
            string line;
            char c;

            vector<string> v;
            while (getline(myfile, line))
            {

                if (!line.empty())
                {
                    v.push_back(line);
                }
            }

            myfile.close();
            myfile.open("todo.txt", ios::out | ios::trunc);

            for (int i = 0; i < v.size(); i++)
            {
                myfile << v[i] << endl;
            }
            pending = v.size();

            v.clear();

            myfile1.clear();
            myfile1.seekg(0);

            while (getline(myfile1, line))
            {

                if (!line.empty())
                {
                    v.push_back(line);
                }
            }

            myfile1.close();
            myfile1.open("done.txt", ios::out | ios::trunc);

            for (int i = 0; i < v.size(); i++)
            {
                myfile1 << v[i] << endl;
            }

            completed = v.size();

            cout << " Pending : " << pending << " "
                 << "Completed : " << completed;
        }
    }

    return 0;
}
