#include<iostream>
#include<string>
using namespace std;


class User;
class Seller;
class Customer;
class Product;
class Order;
class cart;
class CartDetails;
class wishlist;
class payment;

/// Product Class

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




/// User Class

class User
{
protected:
	string userName;
	string password;
	int Id;
public:
	User(string userName, string password, int Id);
	~User() {}
};

User::User(string userName, string password, int Id)
{
	this->userName = userName;
	this->password = password;
	this->Id = Id;
}




/// Seller Class

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


///// Wishlist Class

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


/// CartDetails Class

class CartDetails
{
private:
	int cartDetailNo;
	int OrderIdNo;
	float Amount;
	int quantity;
	Product* P;

public:
	CartDetails(Product* P, int cartDetailNo, int Q);
	float getAmount();
	int getcartDetailNo();
	void viewDetails();
};
CartDetails::CartDetails(Product* P, int cartDetailNo, int Q)
{
	this->cartDetailNo = cartDetailNo;
	this->Amount = P->getPrice() * Q;
	quantity = Q;
	this->P = P;
}
float CartDetails::getAmount()
{
	return this->Amount;
}
int CartDetails::getcartDetailNo()
{
	return this->cartDetailNo;
}
void CartDetails::viewDetails()
{
	cout << "Detail No : " << cartDetailNo << endl;
	cout << "Product Name: " << P->getName() << endl;
	cout << "Quantity : " << quantity << endl;
	cout << "SubTotal : " << Amount << endl;
	cout << "==============" << endl;
}


///// Cart Class
class cart
{
private:
	CartDetails* OD[10];
	Customer* cmr;
	int cartDetailNo;
	double Total;
public:
	cart(Customer* cmr);
	void addcartDetails(Product* P, int Q);
	void Displaycart();
	void setOrderid();
	double getTotal();
	~cart();
};
cart::cart(Customer* cmr)
{
	cartDetailNo = 0;
	this->cmr = cmr;
	Total = 0.0;
}

void cart::addcartDetails(Product* P, int Q)
{
	OD[cartDetailNo] = new CartDetails(P,cartDetailNo+1,Q);
	cartDetailNo++;
}
void cart::Displaycart()
{
	cout << " Cart " << endl;
	if (cartDetailNo > 0) {
		for (int j = 0; j < cartDetailNo; j++)
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
	for (int j = 0; j < cartDetailNo; j++)
	{
		OD[j]->viewDetails();
		Total += OD[j]->getAmount();
	}
}
cart::~cart() {
	cout << "Cart deleted" << endl;
}


/// Order Class
class Order
{
private:
	static int orderidcount;
	int orderid;
	string orderStatus;
	Customer *cmr;
	cart *crt;
	payment* pmr;
	string paymentstate;
public:
	Order();
	void setOrder(Customer* cmr);
	void viewOrderDetails();
	void setpayment(payment* pmr);
};
int Order::orderidcount = 1;


//Payment class
class payment{
private:
	double amount;
	string date;
	int paymentid;
	static int paymentidcount;
public:
	payment(double amount, string date);
};
int payment::paymentidcount;

payment::payment(double amount, string date) {
	this->amount = amount;
	this->date = date;
	paymentid = paymentidcount;
}

/// Customer Class

class Customer :public User
{
private:
	wishlist *wish;
	cart *Crt;
	Order *Ord[100];
	static int customerCount;
	int ordno;
public:
	Customer(string Name, string password);
	void dispalyCusDetails();
	void viewShopProducts(Seller* S);
	void addtowishlist(Product *p);
	void addCart(cart* crt);
	void proceedOrder(Order* ord);
	void viewOrders();
	cart* getcart();
	void viewAllProducts(Product* p[]);
	void viewwishlist();
	void viewCart();
	string getName();
	~Customer();
};

int Customer::customerCount = 1;
Customer::Customer(string Name, string password) :User(Name, password, Customer::customerCount)
{
	wish = new wishlist(customerCount);
	ordno = 0;
	customerCount++;
}
void Customer::addtowishlist(Product *p)
{
	wish->savetoWishlist(p);
}
void Customer::addCart(cart *crt)
{
	Crt = crt;
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
	Crt->Displaycart();
}
void Customer::proceedOrder(Order* ord) 
{
	this->Ord[ordno] = ord;
	Ord[ordno]->setOrder(this);
	ordno++;
	
}
cart* Customer::getcart()
{
	return Crt;
}
void Customer::viewOrders() {
	if (ordno > 0) {
		for (int i = 0; i < ordno; i++)
		{
			Ord[i]->viewOrderDetails();
		}
	}
	else {
		cout << "No orders made" << endl;
	}
}
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

Order::Order()
{
	orderid = 0;
	cout << "New order Created" << endl;
	orderStatus = "Processing";
	paymentstate = "Not Paid!!";
}
void Order::setOrder(Customer* cmr)
{
	this->cmr = cmr;
	this->crt = this->cmr->getcart();	
	this->orderid = orderidcount;
	orderidcount++;
}

void Order::setpayment(payment* pmr) {
	this->pmr = pmr;
	paymentstate = "Paid!!";
}

void Order::viewOrderDetails()
{
	if (orderid != 0)
	{
		cout << "OrderId : " << orderid << endl;
		cout << "Customer Name : " << cmr->getName() << endl;
		cout << "Total amount:" << this->crt->getTotal() << endl;
		cout << "Payment State : " << paymentstate << endl;
		cout << "Order Status: " << orderStatus << endl << endl;
		
	}
	else{
		cout << "Order not set!!" << endl;
	}
	
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

	Customer *c1=new Customer("Robert", "Robert123");
	c1->addtowishlist(prd[0]);
	c1->addtowishlist(prd[1]);
	cart* c[5];
	c[0] = new cart(c1);
	c[0]->addcartDetails(prd[0], 6);
	c[0]->addcartDetails(prd[1], 5);
	c1->addCart(c[0]);

	c1->viewCart();

	payment* pmt[5];
	pmt[0] = new payment(c[0]->getTotal(), "19-10-2020");
	
	Order* o1 = new Order();
	c1->proceedOrder(o1);
	o1->viewOrderDetails();
	o1->setpayment(pmt[0]);
	o1->viewOrderDetails();

	for (int i = 0; i < 2; i++)
	{
		delete s[i];
	}
	delete c[0];
	delete c1;
	return 0;
}
