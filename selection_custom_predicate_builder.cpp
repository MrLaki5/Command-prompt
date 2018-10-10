#include "selection_custom_predicate_builder.h"
#include <sstream>

CustomPredicateBuilder *CustomPredicateBuilder::s_instance = nullptr;

CustomPredicateBuilder* CustomPredicateBuilder::instance(){
	if (!(s_instance))
		s_instance = new CustomPredicateBuilder();
	return s_instance;
}

struct predict_buff{
	FileSelectionPredicate *val;
	predict_buff *next;
	predict_buff(FileSelectionPredicate *v, predict_buff *nnext = nullptr) :val(v), next(nnext){}
	~predict_buff(){val = nullptr;}
};

static predict_buff* p_s=nullptr;


CustomPredicate* CustomPredicateBuilder::build(string s, Cropper *crop_obj){
	predict_buff *p_buff= new predict_buff(nullptr);
	p_s = p_buff;
	try{
		stringstream ss;
		char c;
		char word[MAX_PATH] = "";
		string name;
		string dir;
		int i = 0;
		int count1 = 0;		//provera zagrada
		int count2 = 0;		//provera zareza
		FileSelectionPredicate *temp;
		ss << s;
		ss << '\0';
		ss >> name >> name >> name;
		ss >> dir;
		ss >> c;
		while (c){
			switch (c){
			case '=':
				word[i++] = '\0';
				i = 0;
				if (strcmp(word, "name") == 0){
					p_buff = new predict_buff(crop_obj->name_cropp(&ss, dir), p_buff);
				}
				else{
					if (strcmp(word, "size") == 0){
						p_buff = new predict_buff(crop_obj->size_cropp(&ss, dir), p_buff);
					}
					else{
						if (strcmp(word, "time") == 0){
							p_buff = new predict_buff(crop_obj->time_cropp(&ss, dir), p_buff);
						}
						else{
							throw new unknown_predicate();
						}
					}
				}
				break;
			case'(':
				word[i++] = '\0';
				i = 0;
				count1++;
				if (strcmp(word, "AND") == 0){
					count2++;
					p_buff = new predict_buff(new And(), p_buff);
				}
				else{
					if (strcmp(word, "OR") == 0){
						count2++;
						p_buff = new predict_buff(new Or(), p_buff);
					}
					else{
						if (strcmp(word, "XOR") == 0){
							count2++;
							p_buff = new predict_buff(new Xor(), p_buff);
						}
						else{
							if (strcmp(word, "NOT") == 0){
								p_buff = new predict_buff(new Not(), p_buff);
							}
							else{
								throw new unknown_predicate();
							}
						}
					}
				}
				break;
			case')':
				count1--;
				if (count1 < 0)
					throw new unknown_predicate();
				i = 0;
				break;
			case',':
				count2--;
				if (count2 < 0)
					throw new unknown_predicate();
				i = 0;
				break;
			default:
				word[i++] = c;
				break;
			}
			ss >> c;
		}
		if ((count1) || (count2) || (p_buff->val == nullptr))
			throw new unknown_predicate();
		//FileSelectionPredicate *left = nullptr, *right = nullptr;
		FileSelectionPredicate* vector[100];
		int iter = 0;
		for (iter; iter < 100; iter++)
			vector[iter] = nullptr;
		iter = 0;
		while (p_buff->val){
			temp = p_buff->val;
			p_buff = p_buff->next;
			if (temp->check_redy()){
				if (vector[iter]!=nullptr)
					iter++;
				vector[iter] = temp;
			}
			else{
				if (vector[iter] != nullptr){
					temp->getarg(vector[iter--]);
					if (iter < 0){
						iter = 0;
						vector[iter] = nullptr;
					}
					vector[iter + 1] = nullptr;
					if (temp->check_redy()){
						if (vector[iter] != nullptr)
							iter++;
						vector[iter] = temp;
						continue;
					}
				}
				if (vector[iter] != nullptr){
					temp->getarg(vector[iter--]);
					if (iter < 0){
						iter = 0;
						vector[iter] = nullptr;
					}
					vector[iter + 1] = nullptr;
					if (temp->check_redy()){
						if (vector[iter] != nullptr)
							iter++;
						vector[iter] = temp;
						continue;
					}
				}
				throw new unknown_predicate();
			}
		}
		if (iter)
			throw new unknown_predicate();
		return new CustomPredicate(vector[iter], name);
	}
	catch (unknown_predicate *obj){
		predict_buff* temp;
		while (p_s){
			temp = p_s;
			p_s = p_s->next;
			delete temp;
		}
		throw obj;
	}
}
