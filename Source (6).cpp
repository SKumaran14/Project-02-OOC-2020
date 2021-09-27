#include<iostream>
#include<string>
using namespace std;

class Customer;
/// <summary>
/// Product Class
/// </summary>
class Product
{
private:
	string productName;
	string productId;
	string shopId;
	float price;
	int quantity;	
public:
	Product(string productName, string productId, float price, int quantity);
	void setQuantity(int quantity);
	void setPrice(float price);
	void setShopId(string shopId);
	float getPrice();
	string getName();
	void displayProduct();
	~Product();
};
static int productCount=1;
Product::Product(string productName, string productId, float price, int quantity)
{
	this->productName = productName;
	this->productId = productId;
	this->price = price;
	this->quantity = quantity;
	productCount++;
}

void Product::setQuantity(int quantity)
{
	this->quantity = quantity;
}

void Product::setPrice(float price)
{
	this->price = price;
}

void Product::displayProduct()
{
	cout << "product name is :" << productName << endl;
	cout << "Product id is :" << productId << endl;
	cout << "product Price is :" << price << endl;
	cout << "Product quantity is :" << quantity << endl;
	cout << "===================================================" << endl;
}
void Product::setShopId(string shopId)
{
	this->shopId = shopId;
}
float Product::getPrice()
{
	return price;
}
string Product::getName()
{
	return productName;
}
Product::~Product()
{
	cout << "Product deleted (id: " << productId << " )" << endl;
}



/// <summary>
/// User Class
/// </summary>
class User
{
protected:
	string userName;
	string password;
	int Id;
public:
	User(string userName, string password, int Id);
	virtual ~User() {}
};

User::User(string userName, string password, int Id)
{
	this->userName = userName;
	this->password = password;
	this->Id = Id;
}



/// <summary>
/// Seller Class
/// </summary>
class Seller:public User
{
private:
	string shopId;
	Product* prd[100];
	static int ownercount;
	int shopPrdCount;
public:
	Seller(string userName, string password, string shopId);
	void addProduct(Product* prd[],int start,int end);
	string getshopid();
	void viewProducts();
	~Seller();
};

Seller::Seller(string userName, string password, string shopId):User(userName,password,Seller::ownercount)
{
	shopPrdCount = 0;
	this->shopId = shopId;

}

void Seller::addProduct(Product* prd[],int start,int end)
{
	for(int i=start;i<end;i++)
	{
		this->prd[shopPrdCount]=prd[i];
		prd[shopPrdCount]->setShopId(shopId);
		shopPrdCount++;
	}
}
void Seller::viewProducts() 
{
	for (int i = 0; i <  shopPrdCount;i++)
	{
		prd[i]->displayProduct();
	}
}

string Seller::getshopid()
{
	return shopId;
}


Seller::~Seller()
{
	cout << "Seller deleted" << endl;
	for (int i = 0; i < shopPrdCount; i++)
	{
		delete prd[i];
	}
}
int Seller::ownercount = 1;


//
///// <summary>
///// Wishlist Class
///// </summary>
class wishlist
{
private:
	int wishlistId;
	Product* prd[100];
	int procount;
public:
	wishlist(int i);
	void savetoWishlist(Product* p);
	void displayWishlist();
};

wishlist::wishlist(int i)
{
	wishlistId = i;
	procount = 0;
}
void wishlist::savetoWishlist(Product* p)
{
	prd[procount] = p;
	procount++;
}
void wishlist::displayWishlist()
{
	cout  << " Wishlist " << endl;
	if (procount > 0) {
		for (int a = 0; a < procount; a++)
		{
			prd[a]->displayProduct();
		}
	}
	else {
		cout << " No products available!! " << endl;
	}
	
}

/// <summary>
/// OrderDetails Class
/// </summary>
class OrderDetails
{
private:
	int cartDetailNo;
	int OrderIdNo;
	float Amount;
	int quantity;
	Product* P;

public:
	OrderDetails(Product* P, int cartDetailNo, int Q)
	{
		this->cartDetailNo = cartDetailNo;
		this->Amount = P->getPrice() * Q;
		quantity = Q;
		this->P = P;
	}
	float getAmount()
	{
		return this->Amount;
	}
	int getcartDetailNo()
	{
		return this->cartDetailNo;
	}
	void viewDetails()
	{
		cout << "Detail No : " << cartDetailNo << endl;
		cout << "Product Name: " << P->getName() << endl;
		cout << "Quantity : " << quantity << endl;
		cout << "SubTotal : " << Amount << endl;
		cout << "=============="<< endl;
	}
};

///// <summary>
///// Cart Class
///// </summary>
class cart
{
private:
	OrderDetails* OD[10];
	int orderdetailNo;
	double Total;
	Customer* cmr;
public:
	cart(Customer* cmr);
	void addorderDetails(Product* P, int Q);
	void Displaycart();
	void setOrderid();
	double getTotal();
	Customer* getCustomer();
	~cart(){
		cout << "Cart deleted" << endl;
	}
};
cart::cart(Customer *cmr)
{
	this->cmr = cmr;
	orderdetailNo = 0;
	Total = 0.0;
}
void cart::addorderDetails(Product* P, int Q)
{
	OD[orderdetailNo] = new OrderDetails(P,orderdetailNo+1,Q);
	orderdetailNo++;
}
void cart::Displaycart()
{
	cout << " Cart " << endl;
	if (orderdetailNo > 0) {
		for (int j = 0; j < orderdetailNo; j++)
		{
			OD[j]->viewDetails();
			Total+=OD[j]->getAmount();
		}
		cout << " Cart Total :" << Total << endl;
	}
	else
	{
		cout << " No items in Cart!! " << endl;
	}
	cout << " ----------------- " << endl << endl;
	
}

double cart::getTotal()
{
	return Total;
}
void cart::setOrderid()
{
	for (int j = 0; j < orderdetailNo; j++)
	{
		OD[j]->viewDetails();
		Total += OD[j]->getAmount();
	}
}
Customer* cart::getCustomer() {
	return cmr;
}

/// <summary>
/// Order Class
/// </summary>

class Order
{
private:
	static int orderidcount;
	int orderid;
	string orderStatus;
	Customer *cmr;
	cart *crt;
public:
	Order() {		
		orderid = orderidcount;
		cout << "New order id(" << orderid << ") Created" << endl;
		orderStatus = "Processing";
		orderidcount++;		
	}
	void setOrder(cart* crt);
	void viewOrderDetails();

};
int Order::orderidcount = 1;
/// <summary>
/// Customer Class
/// </summary>
class Customer :public User
{
private:
	wishlist *wish;
	cart *C;
	Order *Ord[100];
	static int j;
	int ordno;
public:
	Customer(string Name, string password);
	void dispalyCusDetails();
	void viewShopProducts(Seller* S);
	void addtowishlist(Product *p);
	void addCart(cart *crt);
	void viewAllProducts(Product* p[]);
	void viewwishlist();
	void viewCart();
	string getName();
	//void proceedOrder(Order *ord);
	~Customer();
};

int Customer::j = 1;
Customer::Customer(string Name, string password) :User(Name, password, Customer::j)
{
	wish = new wishlist(j);
	ordno = 0;
	j++;
}
void Customer::addtowishlist(Product *p)
{
	wish->savetoWishlist(p);
}
void Customer::addCart(cart *crt)
{
	C = crt;
}
void Customer::dispalyCusDetails()
{
	cout << " User Name :" << userName << endl;
	cout << " Customer ID :" << Id << endl;
	cout << "===================================================" << endl;
}
void Customer::viewAllProducts(Product *p[])
{
	for (int i = 0; i < productCount-1; i++)
	{
		p[i]->displayProduct();
	}
}
void Customer::viewShopProducts(Seller *S)
{
		cout << "Shop id :" << S->getshopid() << endl;
		S->viewProducts();
}
void Customer::viewwishlist()
{
	dispalyCusDetails();
	wish->displayWishlist();
}
void Customer::viewCart()
{
	dispalyCusDetails();
	C->Displaycart();
}
//void Customer::proceedOrder(Order* ord) 
//{
//	this->Ord[ordno] = ord;
//	Ord[ordno]->setOrder(this, C);
//	ordno++;
//	
//}
string Customer::getName()
{
	return userName;
}

Customer::~Customer()
{
	cout << "Customer deleted" << endl;
	delete wish;
}



//Implementation of order class
void Order::setOrder(cart* crt)
{
	this->crt = crt;
	this->cmr = crt->getCustomer();
}


void Order::viewOrderDetails()
{
	cout << "OrderId : " << orderid << endl;
	cout << "Customer Name : " << cmr->getName() << endl;
	cout << "Total amount:" << this->crt->getTotal() << endl;
	cout << "Order Status: " << orderStatus << endl << endl;
}





int main()
{
	Seller *s[5];
	s[0]=new Seller("Machael", "mic123", "SHP001");
	s[1] = new Seller("Romanoff", "rom123", "SHP002");

	Product *prd[5];
	prd[0] = new Product("Book", "PRD001", 550.0, 45);
	prd[1] = new Product("Magazine", "PRD002", 980.2, 85);
	prd[2] = new Product("pen", "PRD003", 10.0, 100);

	s[0]->addProduct(prd,0,2);
	s[1]->addProduct(prd,2,3);
	//s[0]->viewProducts();

	Customer *c1=new Customer("Robert", "Robert123");
	//c1.viewShopProducts(s[0]);
	//c1.viewShopProducts(s[1]);
	//c1.dispalyCusDetails();
	c1->addtowishlist(prd[0]);
	c1->addtowishlist(prd[1]);
	cart* c[5];
	c[0] = new cart(c1);
	c[0]->addorderDetails(prd[0],6);
	c[0]->addorderDetails(prd[1],5);
	c1->addCart(c[0]);
	c1->viewCart();
	
	Order* o1 = new Order();
	o1->setOrder(c[0]);
	//delete c1;
	//c1.viewwishlist();
	//c1.viewAllProducts(prd);
	o1->viewOrderDetails();

	for (int i = 0; i < 1; i++)
	{
		delete s[i];
	}
	delete c1;
	return 0;
}