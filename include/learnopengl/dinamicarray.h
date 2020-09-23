#ifndef DINAMICARRAY_H
#define DINAMICARRAY_H

template<class T>
struct DinamicArray{
	T *arr;
	int size;
	DinamicArray(){
		size=0;
		arr=new T[size];
	}
	DinamicArray(const DinamicArray& o) {
		size = o.size;
		arr = new T[size];
		for (int i = 0; i < o.size; i++) {
			arr[i] = o.arr[i];
		}
	}
	
	void resize(int newsize){
		if(newsize<0)
			return;
		int minsize=size>newsize ? newsize : size;
		T *temp=new T[newsize];
		for(int i=0;i<minsize;i++)
			temp[i]=arr[i];
		size=newsize;
		delete[] arr;
		arr=temp;
	}
	
	void push_back(T element){
		resize(size+1);
		arr[size-1]=element;
	}
	
	void addArray(DinamicArray<T>* o){
		for(int i=0;i<o->getSize();i++)
			push_back(o->arr[i]);
	}
	
	void clear_segment(int a,int b){
		if(b>size)
			return;
		int itr=size-1-b;
		for(int i=0;i<itr;i++){
			arr[a+i]=arr[b+i+1];
		}
		resize(size-b+a-1);
	}

	void clearElement(int elementpos) {
		for (int i = elementpos; i < size-1; i++)
			arr[i] = arr[i + 1];
		resize(size - 1);
	}
  
	void clear(){
		resize(0);
	}
	
	int getSize()const{
		return size;
	}
	~DinamicArray(){
		delete[] arr;
	}
};


#endif
