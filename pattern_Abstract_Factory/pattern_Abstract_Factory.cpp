#include<iostream>

using namespace std;
/* Паттерн "Абстрактная фабрика" представляет собой порождающий шаблон проектирования,
   который предоставляет интерфейс для создания связанных или зависимых объектов,
   не указывая их конкретных классов.*/

// Интерфейс Продукта объявляет операции, которые должны выполнять все конкретные продукты.
class Herbivore // Травоядное животное - абстрактный продукт
{
public:
	virtual ~Herbivore() {}
	virtual void EatGrass() = 0;
	virtual double GetWeight() const = 0;
	virtual bool IsAlive() const = 0;
};
class Carnivore  // Плотоядное животное - абстрактный продукт
{
public:
	virtual ~Carnivore() {}
	virtual void Eat(Herbivore& herbivore) = 0;
	virtual double GetPower() const = 0;
	virtual bool IsAlive() const = 0;
};
// Конкретные Продукты предоставляют различные реализации интерфейса Продукта
//----Плотоядные----//
class Wildebeest : public Herbivore // Антилопа Гну - конкретный продукт
{
	double weight;
	bool alive;

public:
	Wildebeest() : weight(150), alive(true) {}
	virtual void EatGrass() { weight += 10; }
	virtual double GetWeight() const { return weight; }
	virtual bool IsAlive() const { return alive; }
};
class Bison : public Herbivore // Бизон - конкретный продукт
{
	double weight;
	bool alive;
public:
	Bison() : weight(450), alive(true) {}
	virtual void EatGrass() { weight += 10; }
	virtual double GetWeight() const { return weight; }
	virtual bool IsAlive() const { return alive; }
};
class Elk : public Herbivore // Лось - конкретный продукт
{
	double weight;
	bool alive;
public:
	Elk() : weight(400), alive(true) {}
	virtual void EatGrass() { weight += 10; }
	virtual double GetWeight() const { return weight; }
	virtual bool IsAlive() const { return alive; }
};
//-----Хищники----//
class Lion : public Carnivore // Лев - конкретный продукт
{
	double power;
	bool alive;

public:
	Lion() : power(50), alive(true) {}
	virtual void Eat(Herbivore& herbivore)
	{
		if (power > herbivore.GetWeight())
		{
			power += 10;
			herbivore.~Herbivore();
		}
		else
			power -= 10;
	}
	virtual double GetPower() const { return power; }
	virtual bool IsAlive() const { return alive; }
};
class Wolf : public Carnivore // Волк - конкретный продукт
{
	double power;
	bool alive;

public:
	Wolf() : power(30), alive(true) {}

	virtual void Eat(Herbivore& herbivore)
	{
		if (power > herbivore.GetWeight())
		{
			power += 10;
			herbivore.~Herbivore();
		}
		else
			power -= 10;

	}
	virtual double GetPower() const { return power; }
	virtual bool IsAlive() const { return alive; }
};
class Tiger : public Carnivore // Тигр - конкретный продукт
{
	double power;
	bool alive;
public:
	Tiger() : power(100), alive(true) {}

	virtual void Eat(Herbivore& herbivore)
	{
		if (power > herbivore.GetWeight())
		{
			power += 10;
			herbivore.~Herbivore();
		}
		else
			power -= 10;

	}
	virtual double GetPower() const { return power; }
	virtual bool IsAlive() const { return alive; }
};

// Класс Создатель объявляет фабричный метод, который должен возвращать объект класса Продукт.
// Подклассы Создателя обычно предоставляют реализацию этого метода.
class Continent // Континент - абстрактная фабрика
{
public:
	virtual Herbivore* createHerbivore() = 0;
	virtual Carnivore* createCarnivore() = 0;
	virtual ~Continent() {}
};
class Africa : public Continent // Африка - конкретная фабрика
{
public:
	Herbivore* createHerbivore() override { return new Wildebeest(); }
	Carnivore* createCarnivore() override { return new Lion(); }
};
class NorthAmerica : public Continent // Северная Америка - конкретная фабрика
{
public:
	Herbivore* createHerbivore() override { return new Bison(); }
	Carnivore* createCarnivore() override { return new Wolf(); }
};
//class Eurasia : public Carnivore // Евразия -  конкретная фабрика
//{
//public:
//	Herbivore* createCarnivore() override { return new Elk(); }
//	Carnivore* createCarnivore() override { return new Tiger(); }
//};

class AnimalWorld // Мир животных – клиент
{
public:
	void MealsHerbivores(Continent* continent) // Питание травоядных
	{
		Herbivore* herbivore = continent->createHerbivore();
		if (herbivore)
		{
			cout << "Травоядное питается травой." << endl;
			herbivore->EatGrass();
		}
		else
			cout << "На этом континенте нет травоядных.." << endl;
	}
	void NutritionCarnivores(Continent* continent) // Питание плотоядных
	{
		Carnivore* carnivore = continent->createCarnivore();
		Herbivore* herbivore = continent->createHerbivore();

		if (carnivore && herbivore)
		{
			cout << "Плотоядное поедает травоядное." << endl;
			carnivore->Eat(*herbivore);
		}
		else if (!carnivore)
			cout << "На этом континенте нет плотоядных.." << endl;
		else
			cout << "На этом континенте нет травоядных.." << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "");

	Continent* africa = new Africa();
	Continent* northAmerica = new NorthAmerica();
	//Continent* eurasua = new Eurasia();

	Herbivore* wildebeest = africa->createHerbivore();
	Herbivore* bison = northAmerica->createHerbivore();
	//Herbivore* elk = eurasua->createHerbivore();

	Carnivore* lion = africa->createCarnivore();
	Carnivore* wolf = northAmerica->createCarnivore();
	//Carnivore* tiger = eurasua->createCarnivore();

	AnimalWorld world;
	world.MealsHerbivores(africa);
	world.NutritionCarnivores(northAmerica);

	return 0;
}