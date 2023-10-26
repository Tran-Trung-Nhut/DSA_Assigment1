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
				~queue(){
					this->delete_All();
				}

				void delete_All(){
					if(this->count == 0) return;
					while(true){
						if(this->count == 1){
							delete this->head;
							this->tail = this->head = nullptr;
							this->count = 0;
							break;
						}
						customer* deleteCus = this->head;
						this->head = this->head->next;
						this->head->prev = nullptr;
						this->count -= 1;
						delete deleteCus;
					}
				}

				int size(){
					return this->count;
				}

				void enqueue_without_MAXSIZE(customer* cus){
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

				customer* get_tail(){
					return this->tail;
				}

				void set_head(customer* cus){
					this->head = cus;
				}

				void set_tail(customer* cus){
					this->tail = cus;
				}

				int get_position(string name){
					int pos = 0;
					customer* tmpCus = this->head;
					for(int i = 0; i < this->count ;i++){
						if(tmpCus->name == name){
							return pos;
						}
						tmpCus = tmpCus->next;
						pos += 1;
					}
					return pos;
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
				
				customer* getTable(){
					if(this->count == 0) return nullptr;
					customer* cus = this->head;
					if(this->count == 1){
						this->head = nullptr;
						this->tail = nullptr;
						this->count -= 1;
						cus->next = cus->prev = nullptr;
						return cus;
					}
					this->head = this->head->next;
					this->head->prev = nullptr;
					this->count -= 1;
					cus->next = cus->prev = nullptr;
					return cus;
				}

				void r_Print(){
					customer* tmpCus = this->tail;
					for(int i = 0; i < this->count; i++){
						tmpCus->print();
						tmpCus = tmpCus->prev;
					}
				}

				customer* get(){
					return this->head;
				}

				bool empty(){
					return this->count == 0;
				}

				void Swap_in_Queue(customer* cus1, customer* cus2){
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

			//Còn oán linh hay không nhỉ?
				bool Out_of_Curses_cus(){
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
				bool Out_of_Sorcerers_cus(){
					customer* tmpCus = tail;
					for(int i = 0; i < this->count;i++){
						if(tmpCus->energy > 0){
							return false;
						}
						tmpCus = tmpCus->prev;
					}
					return true;
				}

				//Loại bỏ oán linh vô sớm nhất trả về tên của nó
				customer* Delete_one_Curses_to_print(){
					customer* tmpCus = this->head;
					for(int i = 0; i < this->count; i++){
						if(tmpCus->energy < 0){
							if(this->count == 1){
								customer* delete_cus = this->head;
								delete_cus->next = delete_cus->prev = nullptr;
								this->head = nullptr;
								this->tail = nullptr;
								this->count = 0;
								return delete_cus;
							}
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
							
							tmpCus->next = tmpCus->prev = nullptr;
							this->count--;
							return tmpCus;
						}
						tmpCus = tmpCus->next;
					}
					return nullptr;
				}

				//Loại bỏ thằng thuật sư vào sớm nhất trả về tên của nó
				customer* Delete_one_Sorcerers_to_print(){
					customer* tmpCus = this->head;
					for(int i = 0; i < this->count; i++){
						if(tmpCus->energy > 0){
							if(this->count == 1){
								customer* delete_cus = this->head;
								delete_cus->next = delete_cus->prev = nullptr;
								this->head = nullptr;
								this->tail = nullptr;
								this->count = 0;
								return delete_cus;
							}
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
							tmpCus->next = tmpCus->prev = nullptr;
							this->count--;
							return tmpCus;
						}
						tmpCus = tmpCus->next;
					}
					return nullptr;
				}

				bool isExist(string name){
					if(this->count == 0) return false;
					customer* tmpCus = this->head;
					for(int i = 0;i < this->count;i++){
						if(tmpCus->name == name){
							return true;
						}else{
							tmpCus = tmpCus->next;
						}
					}
					return false;
				}

				void Delete_cus_with_name(string name){
					customer* tmpCus = this->head;
					for(int i = 0; i < this->count; i++){
						if(tmpCus->name == name){
							if(this->count == 1){	
								delete this->head;
								this->head = nullptr;
								this->tail = nullptr;
								this->count = 0;
								return;
							}
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
							delete tmpCus;
							this->count--;
							return;
						}
						tmpCus = tmpCus->next;
					}
				}
		};
	public:
		queue* Queue = new queue();
		queue* Order = new queue();
	public:

		imp_res() : current(nullptr), number_of_people(0) {};
		~imp_res(){
			this->delete_All_Res();
			delete Queue;
			delete Order;
		}

		void delete_All_Res(){
			if(this->number_of_people == 0) return;
			while(true){
				if(this->number_of_people == 1){
					delete this->current;
					this->current = nullptr;
					this->number_of_people = 0;
					break;
				}
				customer* deleteCus = this->current;
				this->current = this->current->next;
				delete deleteCus;
				this->number_of_people -= 1;
			}
		}

		//Cập nhật vị trí khách hàng
		void updateCustomer(customer* cus) {
			cus->prev->next = cus;
			cus->next->prev = cus;
		}

		void Swap_in_Table(customer* cus1, customer* cus2){
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
		}

		void resetTable(){
			for(int i = 0; i < this->number_of_people;i++){
				customer* out_res = this->current;
				this->Order->Delete_cus_with_name(out_res->name);
				this->current = this->current->next;
				delete out_res;
			}
			this->number_of_people = 0;
			this->current = nullptr;
		}

		//Đuổi oán linh và trả vị trị X về người bên trái
		void Delete_Curses_for_CircularLL(customer* out_res){
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
		void Delete_Sorcerers_for_CircularLL(customer* out_res){
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

			//Cùng tên với khách đã đến trước đó => cút
			customer *tmpCus = this->Order->get();
			for(int i = 0;i < this->Order->size(); i++){
				if(tmpCus->name == name) return;
				tmpCus = tmpCus->next;
			}

			//Vào quán thôi
			customer *cus = new customer (name, energy, nullptr, nullptr);


			//Đủ người rồi đứng chờ đi
			if(this->number_of_people == MAXSIZE){
				//Hàng đợi chưa đủ thì vô hàng đợi không thì cút
				if(this->Queue->size() < MAXSIZE){
					//Đưa vào thứ tự đến quán luôn
					customer* Order_cus = new customer(cus->name,cus->energy,nullptr,nullptr);
					this->Order->enqueue_without_MAXSIZE(Order_cus);
					this->Queue->enqueue(cus);
				}else{
					delete cus;
				}
				return;
			}else{
				//Đưa vào thứ tự đến quán luôn
				customer* Order_cus = new customer(cus->name,cus->energy,nullptr,nullptr);
				this->Order->enqueue_without_MAXSIZE(Order_cus);
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
				this->resetTable();
			}else{
				customer* out_res = this->current;
				for(int i = 0 ;i < num;i++){
					customer* out_cus = this->Order->get();
					
					while(out_cus != nullptr){
						if(this->Queue->isExist(out_cus->name)){
							out_cus = out_cus->next;
						}else{
							break;
						}
					}

					if(out_cus == nullptr){
						return;
					}

					do{
						//Tìm người đến trước nhất để xóa
						if(out_res->name == out_cus->name){
							if(out_res->energy > 0){
								this->Order->Delete_cus_with_name(out_res->name);
								this->Delete_Sorcerers_for_CircularLL(out_res);
							}else{
								this->Order->Delete_cus_with_name(out_res->name);
								this->Delete_Curses_for_CircularLL(out_res);
							}
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

			//Trường hợp chỉ có 2 người trong hàng đợi và trị tuyệt đối energy của người đứng sau lớn hơn người đứng trước thì đổi
			if(this->Queue->size() == 2 && abs(this->Queue->get()->energy) < abs(this->Queue->get_tail()->energy)){
				this->Queue->set_tail(this->Queue->get());
				this->Queue->set_head(this->Queue->get()->next);
				this->Queue->get()->next = this->Queue->get_tail();
				this->Queue->get_tail()->prev = this->Queue->get();
				return this->BLUE(1%MAXSIZE);;
			}else if(this->Queue->size() == 2){return;}

			customer* order_cus = this->Order->get_tail();
			customer* PosMax = nullptr;
			int MaxValue = INT16_MIN;
			for(int i = 0; i < this->Order->size(); i++){
				if(MaxValue < abs(order_cus->energy) && this->Queue->isExist(order_cus->name)){
					MaxValue = abs(order_cus->energy);
					PosMax = order_cus;
				}
				order_cus = order_cus->prev;
				if(order_cus == nullptr) break;
			}	

			int times = 0;

			customer* tmpCus = this->Queue->get();

			//Tìm khách có giá trị tuyệt đối lớn nhất đang đứng đâu đó trong hàng đợi
			for(int i = 0 ;i < this->Queue->size() ;i++){
				if(PosMax->name == tmpCus->name){
					MaxValue = abs(PosMax->energy);
					PosMax = tmpCus;
					break;
				}
				tmpCus = tmpCus->next;
			}

			//Tìm độ dài hàng đợi cần sắp xếp
			tmpCus = this->Queue->get();
			int len = 1;
			while(tmpCus != PosMax){
				len += 1;
				tmpCus = tmpCus->next;
			}

			for(int gap = len/2; gap > 2;gap /= 2){
				for(int i = gap; i < len;i += 1){
					int j = i;
					customer* tmpj = this->Queue->get();
					for(int t = 0; t < j;t++){
						tmpj = tmpj->next;
					}

					customer* tmpj_sub_gap = this->Queue->get();
					for(int t = 0; t < j-gap; t++){
						tmpj_sub_gap = tmpj_sub_gap->next;
					}
					
					while((abs(tmpj_sub_gap->energy) < abs(tmpj->energy) && j >= gap) || (abs(tmpj_sub_gap->energy) == abs(tmpj->energy) && this->Order->get_position(tmpj_sub_gap->name) > this->Order->get_position(tmpj->name) && j >= gap)){
						this->Queue->Swap_in_Queue(tmpj_sub_gap,tmpj);
						times += 1;
						j -= gap;
						tmpj_sub_gap = this->Queue->get();
						for(int t = 0; t < j-gap;t++){
							tmpj_sub_gap = tmpj_sub_gap->next;
						}
					}
				}
			}

			for(int i = 1; i < len;i += 1){
					int j = i;
					customer* tmpj = this->Queue->get();
					for(int t = 0; t < j;t++){
						tmpj = tmpj->next;
					}

					customer* tmpj_sub_gap = this->Queue->get();
					for(int t = 0; t < j-1; t++){
						tmpj_sub_gap = tmpj_sub_gap->next;
					}
					
					while((abs(tmpj_sub_gap->energy) < abs(tmpj->energy) && j >= 1) || (abs(tmpj_sub_gap->energy) == abs(tmpj->energy) && this->Order->get_position(tmpj_sub_gap->name) > this->Order->get_position(tmpj->name) && j >= 1)){
						this->Queue->Swap_in_Queue(tmpj_sub_gap,tmpj);
						times += 1;
						j -= 1;
						tmpj_sub_gap = this->Queue->get();
						for(int t = 0; t < j-1;t++){
							tmpj_sub_gap = tmpj_sub_gap->next;
						}
					}
				}

			return this->BLUE(times%MAXSIZE);
		}
		
		void REVERSAL()
		{
			if(this->number_of_people == 0 || this->number_of_people == 1) return;

			customer* cusStart_Curses = this->current;
			customer* cusEnd_Curses = this->current->next;
			customer* cusStart_Sorcerers = this->current;
			customer* cusEnd_Sorcerers = this->current->next;
			int pass_Sorcerers = 2;
			int pass_Curses = 2;

			//Tìm 2 oán linh ở đầu và cuối tính từ X
			while(cusStart_Curses->energy > 0 || cusEnd_Curses->energy > 0){
				if(pass_Curses > this->number_of_people && cusEnd_Curses->energy > 0 && cusStart_Curses->energy > 0) break;
				if(cusStart_Curses->energy > 0){
					cusStart_Curses = cusStart_Curses->prev;
					pass_Curses += 1;
				}
				if(cusEnd_Curses->energy > 0){
					cusEnd_Curses = cusEnd_Curses->next;
					pass_Curses += 1;
				}
			}
			
			//Tìm 2 chú thuật sư ở đầu và cuối tính từ X
			while(cusStart_Sorcerers->energy < 0 || cusEnd_Sorcerers->energy < 0){
				if(pass_Sorcerers > this->number_of_people && cusEnd_Sorcerers->energy < 0 && cusStart_Sorcerers->energy < 0) break;
				if(cusStart_Sorcerers->energy < 0){
					cusStart_Sorcerers = cusStart_Sorcerers->prev;
					pass_Sorcerers += 1;
				}
				if(cusEnd_Sorcerers->energy < 0){
					cusEnd_Sorcerers = cusEnd_Sorcerers->next;
					pass_Sorcerers += 1;
				}
			}

			do{
				if(cusStart_Curses->energy < 0 && cusEnd_Curses->energy < 0){
					if(pass_Curses > this->number_of_people) break;
 					Swap_in_Table(cusStart_Curses,cusEnd_Curses);

					customer* tmpCus = cusEnd_Curses;
					cusEnd_Curses = cusStart_Curses;
					cusStart_Curses = tmpCus;

					if(cusStart_Curses->prev == cusEnd_Curses){
						cusStart_Curses = cusEnd_Curses;
						pass_Curses += 1;
					}else{
						cusStart_Curses = cusStart_Curses->prev;
						cusEnd_Curses = cusEnd_Curses->next;
						pass_Curses += 2;
					}
				}else{
					if(pass_Curses >= this->number_of_people && cusEnd_Curses->energy > 0 && cusStart_Curses->energy > 0) break;
					if(cusStart_Curses->energy > 0){
						cusStart_Curses = cusStart_Curses->prev;
						pass_Curses += 1;
					}
					if(cusEnd_Curses->energy > 0){
						cusEnd_Curses = cusEnd_Curses->next;
						pass_Curses += 1;
					}
				}
			}while(cusStart_Curses != cusEnd_Curses);

			do{
				if(cusStart_Sorcerers->energy > 0 && cusEnd_Sorcerers->energy > 0){
					if(pass_Sorcerers > this->number_of_people)  break;
					Swap_in_Table(cusEnd_Sorcerers,cusStart_Sorcerers);

					customer* tmpCus = cusEnd_Sorcerers;
					cusEnd_Sorcerers = cusStart_Sorcerers;
					cusStart_Sorcerers = tmpCus;

					if(cusStart_Sorcerers->prev == cusEnd_Sorcerers){
						cusStart_Sorcerers = cusEnd_Sorcerers;
						pass_Sorcerers += 1;
					}else{
						cusStart_Sorcerers = cusStart_Sorcerers->prev;
						cusEnd_Sorcerers = cusEnd_Sorcerers->next;
						pass_Sorcerers += 2;
					}
				}else{
					if(pass_Sorcerers >= this->number_of_people && cusEnd_Sorcerers->energy < 0 && cusStart_Sorcerers->energy < 0) break;
					
					if(cusStart_Sorcerers->energy < 0){
						cusStart_Sorcerers = cusStart_Sorcerers->prev;
						pass_Sorcerers += 1;
					}
					if(cusEnd_Sorcerers->energy < 0){
						cusEnd_Sorcerers = cusEnd_Sorcerers->next;
						pass_Sorcerers += 1;
					}
				}
			}while(cusStart_Sorcerers != cusEnd_Sorcerers);
		}
		void UNLIMITED_VOID()
		{
			//nếu số người nhỏ hơn 4 thì không làm gì
			if(this->number_of_people < 4){return;}
			customer* tmpCus = this->current;
			customer* start = nullptr;
			customer* end = nullptr;
			int smallestValue = INT16_MAX, maxlen = 4;

			for(int i = 0; i < this->number_of_people;i++){
				customer* tmpCus2 = tmpCus;
				int tmp = 0, tmpValue = 0, tmplen = 4;

				do{
					tmpValue += tmpCus2->energy;
					tmpCus2 = tmpCus2->next;
					tmp += 1;
				}while(tmp < 4);

				if(tmpValue < smallestValue){
					smallestValue = tmpValue;
					start = tmpCus;
					end = tmpCus2->prev;
					maxlen = 4;
				}else if(tmpValue == smallestValue && tmplen == maxlen){
					start = tmpCus;
					end = tmpCus2->prev;
				}
				
				while(tmpCus2 != tmpCus){
					
					tmpValue += tmpCus2->energy;
					tmplen += 1;

					if(smallestValue == tmpValue && tmplen > maxlen){
						maxlen = tmplen;
						start = tmpCus;
						end = tmpCus2;
					}

					if(smallestValue == tmpValue && tmplen == maxlen){
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

			//Tìm khách hàng có energy nhỏ nhất trong dãy
			customer* smallest_cus = start;
			customer* store_cus = start;
			for(int i = 0; i < maxlen;i++){
				if(store_cus->energy < smallest_cus->energy){
					smallest_cus = store_cus;
				}
				store_cus = store_cus->next;
			}

			//in  từ khách hàng có giá trị nhỏ nhất cho tới khác hàng cuối
			store_cus = smallest_cus;
			do{
				store_cus->print();
				store_cus = store_cus->next;
			}while(store_cus != end->next);

			//in từ khách hàng đầu tới khách hàng có giá trị nhỏ nhất
			store_cus = start;
			while(store_cus != smallest_cus){
				store_cus->print();
				store_cus = store_cus->next;
			}
		}
		void DOMAIN_EXPANSION()
		{
			if(this->number_of_people == 0 || this->number_of_people == 1){return;}

			if(this->Order->Out_of_Curses_cus() || this->Order->Out_of_Sorcerers_cus()) return;

			int sum_Sorcerers = 0, sum_Curses = 0;
			customer* tmpCus = this->current;
			queue* to_Print = new queue();
			
			//Tổng năng lượng của chú thuật sư và tổng năng lượng của oán linh có mặt tại nhà hàng
			tmpCus = this->Order->get();
			for(int i = 0; i < this->Order->size();i++){
				if(tmpCus->energy >  0){
					sum_Sorcerers += tmpCus->energy;
				}else{
					sum_Curses += tmpCus->energy;
				}
				tmpCus = tmpCus->next;
			}

			if(sum_Sorcerers >= abs(sum_Curses)){
				while(!this->Order->Out_of_Curses_cus()){
					customer* Curses = this->Order->Delete_one_Curses_to_print();
					
					if(!this->Queue->isExist(Curses->name)){
						customer* out_res = this->current;
						while(true){
							if(out_res->name == Curses->name){
								to_Print->enqueue_without_MAXSIZE(Curses);
								this->Delete_Curses_for_CircularLL(out_res);
								break;
							}else{
								out_res = out_res->next;
							}
						}
					}else{
						customer* out_res = this->Queue->get();
						while(true){
							if(out_res->name == Curses->name){
								this->Queue->Delete_cus_with_name(out_res->name);
								to_Print->enqueue_without_MAXSIZE(Curses);
								break;
							}else{
								out_res = out_res->next;
							}
						}
					}
				}
				
			}else{			
				while(!this->Order->Out_of_Sorcerers_cus()){
					customer* Sorcerers = this->Order->Delete_one_Sorcerers_to_print();
					
					if(!this->Queue->isExist(Sorcerers->name)){
						customer* out_res = this->current;
						while(true){
							if(out_res->name == Sorcerers->name){
								to_Print->enqueue_without_MAXSIZE(Sorcerers);
								this->Delete_Sorcerers_for_CircularLL(out_res);
								break;
							}else{
								out_res = out_res->next;
							}
						}
					}else{
						customer* out_res = this->Queue->get();
						while(true){
							if(out_res->name == Sorcerers->name){
								to_Print->enqueue_without_MAXSIZE(Sorcerers);
								this->Queue->Delete_cus_with_name(Sorcerers->name);
								break;
							}else{
								out_res = out_res->next;
							}
						}
					}
				}
			}
			to_Print->r_Print();

			delete to_Print;

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
