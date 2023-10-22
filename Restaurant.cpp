#include "main.h"

class imp_res : public Restaurant
{
	public:
		customer* current;
		int number_of_people;
		class queue{
			private:
				int count;
				customer* head;
				customer* tail;
			public:
				queue():head(nullptr),tail(nullptr),count(0){};
				~queue();

				int size(){
					return this->count;
				}

				void enqueue(customer* cus){
					if(this->count < MAXSIZE){
						if(this->count == 0){
							this->head = cus;
							this->tail = cus;
							
						}else{
							cus->prev = this->tail;
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
					if(this->count == 1){
						delete this->head;
						this->head = nullptr;
						this->tail = nullptr;
						this->count -= 1;
						return;
					}
					customer* cus = this->head;
					this->head = this->head->next;
					this->head->prev = nullptr;
					this->count--;
					delete cus;
				}
				
				customer* getTable(){
					if(this->count == 0) return nullptr;
					customer* cus = this->head;
					if(this->count == 1){
						this->head = nullptr;
						this->tail = nullptr;
						this->count -= 1;
						return cus;
					}
					this->head = this->head->next;
					this->head->prev = nullptr;
					this->count -= 1;
					return cus;
				}

				customer* get(){
					return this->head;
				}

				bool empty(){
					return this->count == 0;
				}

				void Swap2Cus(customer* cus1, customer* cus2){
					if(cus1 == this->head && cus2 == this->tail){
						cus2->prev->next = cus1;
						cus1->next->prev = cus2;
						cus2->next = cus1->next;
						cus1->next = nullptr;
						this->head = cus2;
						this->tail = cus1;
						return;
					}
					if(cus1 == this->head){
						if(cus1->next == cus2){
							cus1->prev = cus2;
							cus2->next->prev = cus1;
							cus1->next = cus2->next;
							cus2->prev = nullptr;
							cus2->next = cus1;
							this->head = cus2;
							return;
						}
						cus1->next->prev = cus2;
						cus2->next->prev = cus1;
						cus2->prev->next = cus1;
						customer* tmp = cus1->next;
						cus1->next = cus2->next;
						cus1->prev = cus2->prev;
						cus2->next = tmp;
						this->head = cus2;
						return;
					}
					if(cus2 == this->tail){
						if(cus1->next == cus2){
							cus2->next = cus1;
							cus1->prev->next = cus2;
							cus2->prev = cus1->prev;
							cus1->prev = cus2;
							cus1->next = nullptr;
							this->tail = cus1;
							return;
						}
						cus2->prev->next = cus1;
						cus1->prev->next = cus2;
						cus1->next->prev = cus2;
						customer* tmp = cus2->prev;
						cus2->prev = cus1->prev;
						cus2->next = cus1->next;
						cus1->prev = tmp;
						this->tail = cus1;
						return;
					}
					if(cus1->next == cus2){
						cus1->prev->next = cus2;
						cus2->next->prev = cus1;
						customer* tmp1 = cus1;
						customer* tmp2 = cus1->prev;
						cus1->next = cus2->next;
						cus1->prev = cus2;
						cus2->next = tmp1;
						cus2->prev = tmp2;
						return;
					}
					cus1->prev->next = cus2;
					cus1->next->prev = cus2;
					cus2->next->prev = cus1;
					cus2->prev->next = cus1;
					customer* tmp1 = cus2->next;
					customer* tmp2 = cus2->prev;
					cus2->next = cus1->next;
					cus2->prev = cus1->prev;
					cus1->prev = tmp2;
					cus1->next = tmp1;
				}

				int SortCustomerQueue(){
					if(this->count == 2){
						this->tail = head;
						this->head = this->head->next;
						this->head->next = this->tail;
						this->tail->prev = this->head;
						return 1;
					}

					int times = 0;

					int MaxValue = INT16_MIN;
					customer* tmpCus = this->head;
					customer* PosMax = nullptr;

					//Tìm khách có giá trị tuyệt đối Energy lớn nhất 
					for(int i = 0 ;i < this->count ;i++){
						if(MaxValue <= abs(tmpCus->energy)){
							MaxValue = abs(tmpCus->energy);
							PosMax = tmpCus;
						}
						tmpCus = tmpCus->next;
					}

					//Tìm độ dài hàng đợi cần sắp xếp
					tmpCus = this->head;
					int len = 1;
					while(tmpCus != PosMax){
						len += 1;
						tmpCus = tmpCus->next;
					}

					for(int gap = len/2; gap > 0;gap /= 2){
						for(int i = gap; i < len;i += 1){
							int j = i;
							
							customer* tmpj = this->head;
							for(int t = 0; t < j;t++){
								tmpj = tmpj->next;\
							}

							customer* tmpj_sub_gap = this->head;
							for(int t = 0; t < j-gap; t++){
								tmpj_sub_gap = tmpj_sub_gap->next;
							}
							
							while(abs(tmpj_sub_gap->energy) < abs(tmpj->energy) && j >= gap){
								Swap2Cus(tmpj_sub_gap,tmpj);
								times += 1;
								j -= gap;
								tmpj_sub_gap = this->head;
								for(int t = 0; t < j-gap;t++){
									tmpj_sub_gap = tmpj_sub_gap->next;
								}
							}
						}
					}
					return times;
				}
	
	//Còn oán linh hay không nhỉ?
	bool isOutofYin(){
		customer* tmpCus = tail;
		for(int i = 0; i < this->count;i++){
			if(tmpCus->energy < 0){
				return false;
			}
			tmpCus = tmpCus->prev;
		}
		return true;
	}

	//Còn chú thuật sư không ta
	bool isOutofYang(){
		customer* tmpCus = tail;
		for(int i = 0; i < this->count;i++){
			if(tmpCus->energy > 0){
				return false;
			}
			tmpCus = tmpCus->prev;
		}
		return true;
	}

	//Loại bỏ oán linh vô trễ nhất trả về tên của nó
	string r_outYin_onlyOne(){
		customer* tmpCus = tail;
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

	//Loại bỏ thằng thuật sư vào trễ nhất trả về tên của nó
	string r_outYang_onlyOne(){
		customer* tmpCus = tail;
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

	//Trả về tên của oán linh tới đây gần nhất
	void r_outYin(){
		customer* tmpCus = tail;
		int tmp = this->count;
		for(int i = 0; i < tmp || tmpCus != nullptr; i++){
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
				tmpCus->print();
				customer* deleteNode = tmpCus;
				tmpCus = tmpCus->prev;
				delete deleteNode;
				this->count--;
			}else{
			tmpCus = tmpCus->prev;
			}
		}
	}

	//Trả về tên của chú thuật sư đến gần đây nhất
	void r_outYang(){
		customer* tmpCus = tail;
		int tmp = this->count;
		for(int i = 0; i < tmp || tmpCus != nullptr; i++){
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
				tmpCus->print();
				customer* deleteNode = tmpCus;
				tmpCus = tmpCus->prev;
				delete deleteNode;
				this->count--;
			}else{
			tmpCus = tmpCus->prev;
			}
		}
	}

	void reset_without_print(){
		for(int i = 0; i < this->count; i++){
			customer* out_queue = this->tail;
			this->tail = this->tail->prev;
			delete out_queue;
		}
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}

	void resetQueue_Order(){
		for(int i = 0; i < this->count; i++){
			this->tail->print();
			customer* out_queue = this->tail;
			this->tail = this->tail->prev;
			delete out_queue;
		}
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}

	};
	public:
		queue* Queue = new queue();
		queue* Order = new queue();
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

		void SitWherever (customer* cus){
			this->current = cus;
			this->current->next = cus;
			this->current->prev = cus;
			this->number_of_people += 1;
			customer* cus_order = new customer(cus->name,cus->energy,nullptr,nullptr);
			this->Order->enqueue(cus_order);
		}

		void SitRight(customer* cus){
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
			customer* cus_order = new customer(cus->name,cus->energy,nullptr,nullptr);
			this->Order->enqueue(cus_order);
		}

		void SitLeft(customer* cus){
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
			customer* cus_order = new customer(cus->name,cus->energy,nullptr,nullptr);
			this->Order->enqueue(cus_order);
		}

		void resetRestaurant(){
			for(int i = 0; i < this->number_of_people;i++){
				customer* out_res = this->current;
				this->current = this->current->next;
				delete out_res;
			}
			this->number_of_people = 0;
			this->current = nullptr;
		}

		//Đuổi oán linh và trả vị trị X về người bên trái
		void Yin_out(customer* out_res){
			if(this->number_of_people == 1){
				delete out_res;
				this->current = nullptr;
				this->number_of_people -= 1;
				return;
			}
			if(this->number_of_people == 2){
				this->current = out_res->prev;
				this->current->next = this->current;
				this->current->prev = this->current;
				delete out_res;
				this->number_of_people -= 1;
				return;
			}
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
			if(this->number_of_people == 1){
				delete out_res;
				this->current = nullptr;
				this->number_of_people -= 1;
				return;
			}
			if(this->number_of_people == 2){
				this->current = out_res->next;
				this->current->next = this->current;
				this->current->prev = this->current;
				delete out_res;
				this->number_of_people -= 1;
				return;
			}
			this->current = out_res->next;
			out_res->prev->next = out_res->next;
			out_res->next->prev = out_res->prev;
			out_res->next = nullptr;
			out_res->prev = nullptr;
			delete out_res;
			this->number_of_people -= 1;
		}

		void RED_2(customer* cus){
			if(this->number_of_people >= MAXSIZE/2){
				customer* tmpCus = current;
				int RES = INT16_MIN;
				for(int i = 0;i < this->number_of_people;i++){
					if(RES < abs(cus->energy - tmpCus->energy)){
						this->current = tmpCus;
						RES = abs(cus->energy - tmpCus->energy);
					}
					tmpCus = tmpCus->next;
				}
				
				RES = cus->energy - this->current->energy;
					
				if(this->number_of_people == 0){		 
					this->SitWherever(cus);
				} else{
					//Nếu chênh lệch sức mạnh nhiều nhất là số dương thì ngồi phải
					if(RES > 0){ 
						this->SitRight(cus);
					}
					//Ngược lại
					else{								
						this->SitLeft(cus);
					}
				};
				return;
			}
			//Nếu chưa có khách nào thì khách đầu tiên muốn ngồi đâu cũng say yes	 
			if(this->number_of_people == 0){		 
				this->SitWherever(cus);
			} else{
				//Nếu energy của khách mới lớn hơn thì ngồi bên phải người vào trước đó
				if(cus->energy >= this->current->energy){
					this->SitRight(cus);
				}
				//Và ngược lại
				else{								 
					this->SitLeft(cus);
				}
			}
		}

		void RED(string name, int energy)
		{
			//Energy bằng 0 => cút
			if(energy == 0) return;						

			customer *tmpQueue = this->Queue->get();
			for(int i = 0;i < this->Queue->size(); i++){
				if(tmpQueue->name == name) return;
				tmpQueue = tmpQueue->next;
			}

			//Cùng tên trong bàn=> cút
			customer* tmpCurrent = this->current;
			for(int i = 0 ;i < number_of_people ;i++){
				if(tmpCurrent->name == name) return;
				tmpCurrent = tmpCurrent->next;
			}

			//Vào quán thôi
			customer *cus = new customer (name, energy, nullptr, nullptr);

			//Đủ người rồi đứng chờ đi
			if(this->number_of_people == MAXSIZE){
				this->Queue->enqueue(cus);
				return;
			}

			//Nếu MAXSIZE = 1 và chưa có ai thì ngồi luôn đi má
			if(MAXSIZE == 1 && this->number_of_people == 0){
				this->SitWherever(cus);
				return;
			}

			//Liệu số người vào được 1 nửa số lượng chỗ tối đa chưa
			if(this->number_of_people >= MAXSIZE/2){
				customer* tmpCus = current;
				int RES = INT16_MIN;
				for(int i = 0;i < this->number_of_people;i++){
					if(RES < abs(energy - tmpCus->energy)){
						this->current = tmpCus;
						RES = abs(energy - tmpCus->energy);
					}
					tmpCus = tmpCus->next;
				}
				
				RES = energy - this->current->energy;
					
				if(this->number_of_people == 0){		 
					this->SitWherever(cus);
				} else{
					//Nếu chênh lệch sức mạnh nhiều nhất là số dương thì ngồi phải
					if(RES > 0){ 
						this->SitRight(cus);
					}
					//Ngược lại
					else{								
						this->SitLeft(cus);
					}
				};
				return;
			}
			//Nếu chưa có khách nào thì khách đầu tiên muốn ngồi đâu cũng say yes	 
			if(this->number_of_people == 0){		 
				this->SitWherever(cus);
			} else{
				//Nếu energy của khách mới lớn hơn thì ngồi bên phải người vào trước đó
				if(energy >= this->current->energy){
					this->SitRight(cus);
				}
				//Và ngược lại
				else{								 
					this->SitLeft(cus);
				}
			}

		}

		//Hàng đợi có người thì thêm vào không thì thôi
		void Queue_to_Table(){
			if(!this->Queue->empty() && this->number_of_people < MAXSIZE){
				while(this->number_of_people < MAXSIZE && !this->Queue->empty()){
					customer* cus = this->Queue->getTable();
					this->RED_2(cus);
				}		
			}
			else{return;}			
		}

		void BLUE(int num)
		{
			if(num >= this->number_of_people){
				this->Order->reset_without_print();
				this->resetRestaurant();
			}else{
				customer* out_res = this->current;
				for(int i = 0 ;i < num;i++){
					do{
						//Tìm người đến trước nhất để xóa
						if(out_res->name == this->Order->get()->name){
							if(out_res->energy > 0){
								this->Yang_out(out_res);
							}else{
								this->Yin_out(out_res);
							}
							this->Order->dequeue();
							out_res = this->current;
						}else{
							out_res = out_res->next;
						}
					}while(out_res != this->current);
				}
			}
			this->Queue_to_Table();
		}

		void PURPLE()
		{
			if(this->Queue->size() == 0 || this->Queue->size() == 1) return;
			int N = this->Queue->SortCustomerQueue();
			return this->BLUE(N%MAXSIZE);
		}
		
		void REVERSAL()
		{
			if(this->number_of_people == 0 || this->number_of_people == 1) return;

			customer* cusStart_yin = this->current;
			customer* cusEnd_yin = this->current->next;
			customer* cusStart_yang = this->current;
			customer* cusEnd_yang = this->current->next;
			int pass_yang = 2;
			int pass_yin = 2;

			while(cusStart_yin->energy > 0 || cusEnd_yin->energy > 0){
				if(pass_yin > this->number_of_people && cusEnd_yin->energy > 0 && cusStart_yin->energy > 0) break;
				if(cusStart_yin->energy > 0){
					cusStart_yin = cusStart_yin->prev;
					pass_yin += 1;
				}
				if(cusEnd_yin->energy > 0){
					cusEnd_yin = cusEnd_yin->next;
					pass_yin += 1;
				}
			}
			
			while(cusStart_yang->energy < 0 || cusEnd_yang->energy < 0){
				if(pass_yang > this->number_of_people && cusEnd_yang->energy < 0 && cusStart_yang->energy < 0) break;
				if(cusStart_yang->energy < 0){
					cusStart_yang = cusStart_yang->prev;
					pass_yang += 1;
				}
				if(cusEnd_yang->energy < 0){
					cusEnd_yang = cusEnd_yang->next;
					pass_yang += 1;
				}
			}

			do{
				if(cusStart_yin->energy < 0 && cusEnd_yin->energy < 0){
					if(pass_yin > this->number_of_people) break;
 					swapCustomer(cusStart_yin,cusEnd_yin);
					customer* tmpCus = cusEnd_yin;
					cusEnd_yin = cusStart_yin;
					cusStart_yin = tmpCus;
					if(cusStart_yin->prev == cusEnd_yin){
						cusStart_yin = cusEnd_yin;
						pass_yin += 1;
					}else{
						cusStart_yin = cusStart_yin->prev;
						cusEnd_yin = cusEnd_yin->next;
						pass_yin += 2;
					}
				}else{
					if(pass_yin >= this->number_of_people && cusEnd_yin->energy > 0 && cusStart_yin->energy > 0) break;
					if(cusStart_yin->energy > 0){
						cusStart_yin = cusStart_yin->prev;
						pass_yin += 1;
					}
					if(cusEnd_yin->energy > 0){
						cusEnd_yin = cusEnd_yin->next;
						pass_yin += 1;
					}
				}
			}while(cusStart_yin != cusEnd_yin);

			do{
				if(cusStart_yang->energy > 0 && cusEnd_yang->energy > 0){
					if(pass_yang > this->number_of_people)  break;
					swapCustomer(cusEnd_yang,cusStart_yang);
					customer* tmpCus = cusEnd_yang;
					cusEnd_yang = cusStart_yang;
					cusStart_yang = tmpCus;
					if(cusStart_yang->prev == cusEnd_yang){
						cusStart_yang = cusEnd_yang;
						pass_yang += 1;
					}else{
						cusStart_yang = cusStart_yang->prev;
						cusEnd_yang = cusEnd_yang->next;
						pass_yang += 2;
					}
				}else{
					if(pass_yang >= this->number_of_people && cusEnd_yang->energy < 0 && cusStart_yang->energy < 0) break;
					if(cusStart_yang->energy < 0){
						cusStart_yang = cusStart_yang->prev;
						pass_yang += 1;
					}
					if(cusEnd_yang->energy < 0){
						cusEnd_yang = cusEnd_yang->next;
						pass_yang += 1;
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
			if(this->number_of_people == 0){return;}

			int sum_yang = 0, sum = 0;
			customer* tmpCus = this->current;
			
			//Tính tổng năng lượng của chú thuật sư và tổng năng lượng toàn bộ khách trong bàn
			do{
				if(tmpCus->energy > 0){
					sum_yang += tmpCus->energy;
				}
				sum += tmpCus->energy;
				tmpCus = tmpCus->next;
			}while(tmpCus != this->current);

			//Tổng năng lượng
			tmpCus = this->Queue->get();
			for(int i = 0; i < this->Queue->size();i++){
				if(tmpCus->energy >  0){
					sum_yang += tmpCus->energy;
				}
				sum += tmpCus->energy;
				tmpCus = tmpCus->next;
			}

			if(sum_yang >= abs(sum)){
				this->Queue->r_outYin();
				while(!this->Order->isOutofYin()){
					string Yin_name = this->Order->r_outYin_onlyOne();
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
				this->Queue->r_outYang();
				while(!this->Order->isOutofYang()){
					string Yang_name = this->Order->r_outYang_onlyOne();
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
			this->Queue_to_Table();
		}
		void LIGHT(int num)
		{
			if(num == 0){
				customer* tmpQueue = this->Queue->get();
				for(int i = 0; i < this->Queue->size(); i++){
					tmpQueue->print();
					tmpQueue = tmpQueue->next;
				}
				return;
			}
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

