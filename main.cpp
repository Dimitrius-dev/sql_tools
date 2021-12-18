#include <string>
#include <iostream>
#include <pqxx/pqxx>
#include <list>

class One{
private:
	int id;
	std::string name;
public:
	One(int id, std::string name){
		this->id = id;	
		this->name = name;	
	}


	std::string toString(){
		return ("id: " + std::to_string(this->id) + " name: " + this->name + "\n");
	}
};

void select(std::string config, std::list<One> &one, std::string command){
	one.clear();	

	try
	{
		pqxx::connection connectionObject(config.c_str());
		pqxx::work worker(connectionObject);
		pqxx::result response = worker.exec(command.c_str());

		for (auto row : response) {
			one.push_back(One(row[0].as<int>(), row[1].as<std::string>()));
	    	}

		connectionObject.disconnect();

	}

    	catch (const std::exception& e)
    	{
       		std::cerr << e.what() << std::endl;
    	}
}

void insert(std::string config, std::list<One> &one, std::string command){
	try
	{
		pqxx::connection connectionObject(config.c_str());
		pqxx::work worker(connectionObject);
		pqxx::result response = worker.exec(command.c_str());

		worker.commit();

		connectionObject.disconnect();
	}

    	catch (const std::exception& e)
    	{
       		std::cerr << e.what() << std::endl;
    	}
}

void update(std::string config, std::list<One> &one, std::string command){
	try
	{
		pqxx::connection connectionObject(config.c_str());
		pqxx::work worker(connectionObject);
		pqxx::result response = worker.exec(command.c_str());


	}

    	catch (const std::exception& e)
    	{
       		std::cerr << e.what() << std::endl;
    	}
}

void show(std::list<One> &one){
	for (auto iter = one.begin(); iter != one.end(); iter++){
        	std::cout << iter->toString();
	}
	std::cout<<"-----------\n";
}

int main()
{
	std::string connectionString = "host=localhost port=5432 dbname=maindb user=dmitrii password=dimabelov02";//ostgres password=DimaJane";

	std::list<One> one;

	while(true){
		std::string name;
		std::cin>>name;

		if(name == "show"){
			select(connectionString, one, "SELECT * FROM one");
			show(one);
		}
		else{
			std::string buf = std::string("INSERT INTO one (name) VALUES" ) + "('" + name + "');";
			insert(connectionString, one, buf);
		}
				
	}


	return 0;
}
