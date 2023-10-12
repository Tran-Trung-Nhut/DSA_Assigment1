#include "main.h"


//Hàng đợi khi đã đầy bàn
class queue{
class ValueCustomer;
private:
	int count;
	int maxSize;
	ValueCustomer* head;
	ValueCustomer* tail;
	friend class ValueCustomer;
private:
	class ValueCustomer{
		public:
			ValueCustomer* next;
			int energy;
			string name;
		public:
			ValueCustomer(int e, string na) : energy(e),name(na),next(nullptr){};
			~ValueCustomer(){};
	};
public:
	queue(int size):head(nullptr),tail(nullptr),maxSize(size),count(0){};
	~queue();

	int size(){
		return this->count;
	}
	void enqueue(int e, string na){
		ValueCustomer* cus = new ValueCustomer(e,na);
		if(this->count < this->maxSize){
			if(this->count == 0){
				this->head = cus;
				this->tail = cus;
				
			}else{
				this->tail->next = cus;
				this->tail = cus;
			}
			this->count++;
		}
		else{
			return;
		}
	}
	void dequeue(){
		if(this->count == 0) return;
		ValueCustomer* cus = head;
		this->head = this-> head->next;
		this->count--;
		delete cus;
	}
	
	ValueCustomer* get(){
		return this->head;
	}

	bool empty(){
		return this->count == 0;
	}

	void SortCustomerQueue(){
		int MaxValue = INT16_MIN;
		ValueCustomer* tmpCus = this->head;
		ValueCustomer* PosMax = nullptr;
		for(int i = 0 ;i < this->count ;i++){
			if(MaxValue <= abs(tmpCus->energy)){
				MaxValue = abs(tmpCus->energy);
				PosMax = tmpCus;
			}
			tmpCus = tmpCus->next;
		}
	}

	void print(){
		ValueCustomer* tmpQ = head;
		for(int i = 0; i < this->count;i++){
			cout << tmpQ->name <<"-"<< tmpQ->energy<<endl;
			tmpQ = tmpQ->next;
		}
	}
};

class Order{
class Node;
public:
	Node* head;
	Node* tail;
	int count;
private:
	class Node{
	public:
		Node* next;
		Node* prev;
		string name;
		int energy;
		friend class Order;
	public:
		Node(string na, int e) : name(na),energy(e), next(nullptr){};
		~Node(){};
	};
public:

	Order() : head(nullptr),tail(nullptr), count(0) {};
	bool empty(){
		return this->count == 0;
	}

	void enterRestaurant(string name, int energy){
		Node* cus = new Node(name,energy);
		if(count == 0){
			this->head = cus;
			this->tail = cus;
		}else{
			cus->prev = this->tail;
			this->tail->next = cus;
			this->tail = cus;
		}
		count += 1;
	}

	void outRestaurant(){
		if(this->count == 0) return;
		Node* cus = head;
		this->head = this->head->next;
		this->count--;
		delete cus;
	}

	//Còn hay hết oán linh
	bool isOutofYin(){
		Node* tmpCus = tail;
		for(int i = 0; i < this->count;i++){
			if(tmpCus->energy < 0){
				return false;
			}
			tmpCus = tmpCus->prev;
		}
		return true;
	}

	//Trả về tên của oán linh tới đây gần nhất
	string r_outYin(){
		Node* tmpCus = tail;
		string na;
		for(int i = 0; i < this->count; i++){
			if(tmpCus->energy < 0){
				if(tmpCus == this->tail){
					tmpCus->prev->next = nullptr;
					this->tail = tmpCus->prev;
				}else if(tmpCus == this->head){
					tmpCus->next->prev = nullptr;
					this->head = tmpCus->next;
				}else{
					tmpCus->prev->next = tmpCus->next;
					tmpCus->next->prev = tmpCus->prev;
				}
				na = tmpCus->name;
				delete tmpCus;
				this->count--;
				return na;
			}
			tmpCus = tmpCus->prev;
		}
		return "";
	}

	//Còn hay hết chú thuật sư
	bool isOutofYang(){
		Node* tmpCus = tail;
		for(int i = 0; i < this->count;i++){
			if(tmpCus->energy > 0){
				return false;
			}
			tmpCus = tmpCus->prev;
		}
		return true;
	}

	//Trả về tên của chú thuật sư đến gần đây nhất
	string r_outYang(){
		Node* tmpCus = tail;
		string na;
		for(int i = 0; i < this->count; i++){
			if(tmpCus->energy > 0){
				if(tmpCus == this->tail){
					tmpCus->prev->next = nullptr;
					this->tail = tmpCus->prev;
				}else if(tmpCus == this->head){
					tmpCus->next->prev = nullptr;
					this->head = tmpCus->next;
				}else{
					tmpCus->prev->next = tmpCus->next;
					tmpCus->next->prev = tmpCus->prev;
				}
				na = tmpCus->name;
				delete tmpCus;
				this->count--;
				return na;
			}
			tmpCus = tmpCus->prev;
		}
		return "";
	}

	string get_cus(){
		return head->name;
	}

	int size(){
		return count;
	}
};


class imp_res : public Restaurant
{
	public:
		customer* current;
		int max_People;
		int number_of_people;
	public:
		queue* cusQueue = new queue(this->max_People);
		Order* ValueOrder = new Order();
	public:

		imp_res() : current(nullptr), number_of_people(0) {};
		~imp_res(){
			delete current;
		}

		//Cập nhật vị trí khách hàng
		void updateCustomer(customer* cus) {
			cus->prev->next = cus;
			cus->next->prev = cus;
		}

		void swapCustomer(customer* cus1, customer* cus2){
			if (cus2->next == cus1) {
					customer *temp = cus1;
					cus1 = cus2;
					cus2 = temp;
				}

			if (cus2->next != cus1) {
				customer *n1_prev = cus1->prev;
				customer *n2_next = cus2->next;

				if (cus1->next == cus2) {
					cus1->prev = cus1->next;
					cus2->next = cus2->prev;
				} else {
					cus1->prev = cus2->prev;
					cus2->next = cus1->next;
				}
				cus2->prev = n1_prev;
				cus1->next = n2_next;

				updateCustomer(cus1);
				updateCustomer(cus2);
			}
		}	

		void SitWherever (customer* cus, string name, int energy){
			this->current = cus;
			this->number_of_people += 1;
			this->ValueOrder->enterRestaurant(name,energy);
		}

		void SitRight(customer* cus, string name, int energy){
			cus->prev = this->current;
			if(this->number_of_people == 1){
				this->current->next = cus;
				cus->next = this->current;
				this->current->prev = cus;
			}else{							 
				cus->next = this->current->next;
				this->current->next->prev = cus;
				this->current->next = cus;
			}
			this->current = cus;
			this->number_of_people += 1;
			ValueOrder->enterRestaurant(name, energy);
		}

		void SitLeft(customer* cus, string name,int energy){
			cus->next = this->current;
			if(this->number_of_people == 1){
				
				this->current->prev = cus;
				cus->prev = this->current;
				this->current->next = cus;
			}else{
				cus->prev = this->current->prev;
				this->current->prev->next = cus;
				this->current->prev = cus;
			}
			this->current = cus;
			this->number_of_people += 1;
			ValueOrder->enterRestaurant(name,energy);
		}

		void resetRestaurant(){
			for(int i = 0; i < this->number_of_people;i++){
				customer* out_res = this->current;
				this->current = this->current->next;
				delete[] out_res;
			}
			this->number_of_people = 0;
			this->current = nullptr;
		}

		//Đuổi oán linh và trả vị trị X về người bên trái
		void Yin_out(customer* out_res){
			this->current = out_res->prev;
			out_res->prev->next = out_res->next;
			out_res->next->prev = out_res->prev;
			out_res->next = nullptr;
			out_res->prev = nullptr;
			delete out_res;
			this->number_of_people -= 1;
		}

		//Đuổi chú thuật sư và trả vị trị X về người bên phải
		void Yang_out(customer* out_res){
			this->current = out_res->next;
			out_res->prev->next = out_res->next;
			out_res->next->prev = out_res->prev;
			out_res->next = nullptr;
			out_res->prev = nullptr;
			delete out_res;
			this->number_of_people -= 1;
		}

		void RED(string name, int energy)
		{
			this->max_People = MAXSIZE;
			//Energy bằng 0 => cút
			if(energy == 0) return;						

			//Cùng tên => cút
			customer* tmpCurrent = current;
			for(int i = 0 ;i < number_of_people ;i++){
				if(tmpCurrent->name == name) return;
				tmpCurrent = tmpCurrent->next;
			}

			//Vào quán thôi
			customer *cus = new customer (name, energy, nullptr, nullptr);
			
			//Liệu số người vào được 1 nửa số lượng chỗ tối đa chưa
			if(this->number_of_people >= max_People/2){
				customer* tmpCus = current;
				int RES = INT16_MIN;
				for(int i = 0;i < this->number_of_people;i++){
					if(RES < abs(energy - tmpCus->energy)){
						this->current = tmpCus;
						RES = abs(energy - tmpCus->energy);
					}
					tmpCus = tmpCus->next;
				}
				
				RES = energy - tmpCus->energy;
				if(this->number_of_people < max_People){	
					if(this->number_of_people == 0){		 
						this->SitWherever(cus, name,energy);
					} else{
						//Nếu chênh lệch sức mạnh nhiều nhất là số dương thì ngồi phải
						if(RES > 0){ 
							this->SitRight(cus,name,energy);
						}
						//Ngược lại
						else{								
							this->SitLeft(cus,name,energy);
						}
					};
				}else{
					//Đưa khác vào hàng đợi nếu chỗ đã đủ											
					this->cusQueue->enqueue(cus->energy,cus->name);
					delete cus;
				}
				return;
			}
			//Kiểm tra liệu liệu số khách hiện tại có bằng số khách tối đa chưa
			if(this->number_of_people < max_People){
				//Nếu chưa có khách nào thì khách đầu tiên muốn ngồi đâu cũng say yes	 
				if(this->number_of_people == 0){		 
					this->SitWherever(cus, name, energy);
				} else{
					//Nếu energy của khách mới lớn hơn thì ngồi bên phải người vào trước đó
					if(energy >= this->current->energy){
						this->SitRight(cus, name, energy);
					}
					//Và ngược lại
					else{								 
						this->SitLeft(cus, name, energy);
					}
				}
			}else{	
				//Đưa khách vào hàng đợi nếu chỗ đã đủ
				this->cusQueue->enqueue(cus->energy,cus->name);
				delete cus;
			}

		}
		void BLUE(int num)
		{
			if(num >= this->number_of_people){
				this->resetRestaurant();
			}else{
				customer* out_res = this->current;
				for(int i = 0 ;i < num;i++){
					do{
						//Tìm người đến trước nhất để xóa
						if(out_res->name == this->ValueOrder->get_cus()){
							if(out_res->energy > 0){
								this->Yang_out(out_res);
							}else{
								this->Yin_out(out_res);
							}
							this->ValueOrder->outRestaurant();
							out_res = this->current;
						}else{
							out_res = out_res->next;
						}
					}while(out_res != this->current);
				}
			}
			//Hàng đợi có người thì thêm vào không thì thôi
			if(!this->cusQueue->empty() && this->number_of_people < this->max_People){
				while(this->number_of_people < this->max_People && !this->cusQueue->empty()){
					string na = this->cusQueue->get()->name;
					int e = this->cusQueue->get()->energy;
					this->RED(na,e);
					this->cusQueue->dequeue();
				}		
			}
			else{return;}
		}
		void PURPLE()
		{
			if(this->cusQueue->size() == 0 || this->cusQueue->size() == 1) return;
			this->cusQueue->SortCustomerQueue();
		}
		void REVERSAL()
		{
			
			customer* cusStart_yin = this->current;
			customer* cusEnd_yin = this->current->next;
			customer* cusStart_yang = this->current;
			customer* cusEnd_yang = this->current->next;

			while(cusStart_yin->energy > 0 || cusEnd_yin->energy > 0){
				if(cusStart_yin->energy > 0){
					cusStart_yin = cusStart_yin->prev;
				}
				if(cusEnd_yin->energy > 0){
					cusEnd_yin = cusEnd_yin->next;
				}
			}
			
			while(cusStart_yang->energy < 0 || cusEnd_yang->energy < 0){
				if(cusStart_yang->energy < 0){
					cusStart_yang = cusStart_yang->prev;
				}
				if(cusEnd_yang->energy < 0){
					cusEnd_yang = cusEnd_yang->next;
				}
			}

			do{
				if(cusStart_yin->energy < 0 && cusEnd_yin->energy < 0){
					swapCustomer(cusStart_yin,cusEnd_yin);
					customer* tmpCus = cusEnd_yin;
					cusEnd_yin = cusStart_yin;
					cusStart_yin = tmpCus;
					if(cusStart_yin->prev == cusEnd_yin){
						cusStart_yin = cusEnd_yin;
					}else{
						cusStart_yin = cusStart_yin->prev;
						cusEnd_yin = cusEnd_yin->next;
					}
				}else{
					if(cusStart_yin->energy > 0){
						cusStart_yin = cusStart_yin->prev;
					}
					if(cusEnd_yin->energy > 0){
						cusEnd_yin = cusEnd_yin->next;
					}
				}
			}while(cusStart_yin != cusEnd_yin);

			do{
				if(cusStart_yang->energy > 0 && cusEnd_yang->energy > 0){
					swapCustomer(cusEnd_yang,cusStart_yang);
					customer* tmpCus = cusEnd_yang;
					cusEnd_yang = cusStart_yang;
					cusStart_yang = tmpCus;
					if(cusStart_yang->prev == cusEnd_yang){
						cusStart_yang = cusEnd_yang;
					}else{
						cusStart_yang = cusStart_yang->prev;
						cusEnd_yang = cusEnd_yang->next;
					}
				}else{
					if(cusStart_yang->energy < 0){
						cusStart_yang = cusStart_yang->prev;
					}
					if(cusEnd_yang->energy < 0){
						cusEnd_yang = cusEnd_yang->next;
					}
				}
			}while(cusStart_yang != cusEnd_yang);
		}
		void UNLIMITED_VOID()
		{
			//nếu số người nhỏ hơn 4 thì không làm gì
			if(this->number_of_people < 4){return;}
			customer* tmpCus = this->current;
			customer* start = nullptr;
			customer* end = nullptr;
			int smallestValue = INT16_MAX, maxlen = 4;
			for(int i = 0; i < this->number_of_people - 3;i++){
				customer* tmpCus2 = tmpCus;
				int tmp = 0, tmpValue = 0, tmplen = 4;
				do{
					tmpValue += tmpCus2->energy;
					tmpCus2 = tmpCus2->next;
					tmp += 1;
				}while(tmp < 4 && tmpCus2 != this->current);
				if(tmpValue < smallestValue){
					smallestValue = tmpValue;
					start = tmpCus;
					end = tmpCus2;
					maxlen = 4;
				}
				while(tmpCus2 != this->current){
					tmpValue += tmpCus2->energy;
					tmplen += 1;
					if(smallestValue == tmpValue && tmplen > maxlen){
						maxlen = tmplen;
						start = tmpCus;
						end = tmpCus2;
					}
					if(tmpValue < smallestValue){
						smallestValue = tmpValue;
						maxlen = tmplen;
						start = tmpCus;
						end = tmpCus2;
					}
					tmpCus2 = tmpCus2->next;
				}
				tmpCus = tmpCus->next;
			}
			//in  ra đến end thì dừng lại
			while(start != end->next){
				start->print();
				start = start->next;
			}
		}
		void DOMAIN_EXPANSION()
		{
			int sum_yang = 0, sum_yin = 0;
			customer* tmpCus = this->current;

			do{
				if(tmpCus->energy > 0){
					sum_yang += tmpCus->energy;
				}else{
					sum_yin += tmpCus->energy;
				}
				tmpCus = tmpCus->next;
			}while(tmpCus != this->current);

			if(sum_yang == abs(sum_yin)){
				this->resetRestaurant();
			}else if(sum_yang > abs(sum_yin)){
				while(!this->ValueOrder->isOutofYin()){
					string Yin_name = this->ValueOrder->r_outYin();
					customer* out_res = this->current;
					
					do{
						if(out_res->name == Yin_name){
							out_res->print();
							this->Yin_out(out_res);
							out_res = this->current;
						}else{
							out_res = out_res->next;
						}
					}while(out_res != this->current);
				}
			}else{
				while(!this->ValueOrder->isOutofYang()){
					string Yang_name = this->ValueOrder->r_outYang();
					customer* out_res = this->current;
					
					do{
						if(out_res->name == Yang_name){
							out_res->print();
							this->Yang_out(out_res);
							out_res = this->current;
						}else{
							out_res = out_res->next;
						}
					}while(out_res != this->current);
				}
			}
		}
		void LIGHT(int num)
		{
			if(num == 0) this->cusQueue->print();
			customer* tmpI = this->current;
			if(num > 0){
				for(int i = 0; i < this->number_of_people;i++){
					tmpI->print();
					tmpI = tmpI->next;
				}
			}
			else{
				for(int i = 0; i < this->number_of_people;i++){
					tmpI->print();
					tmpI = tmpI->prev;
				}
			}
		}
};

