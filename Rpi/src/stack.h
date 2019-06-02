
#ifndef 	_INCL_STACK
#define		_INCL_STACK

#define		DEFAULT_DEPTH			64

class Array
{
	private:
		void **			array;
		size_t			depth;
		size_t			itemCount;
		
		void			initialise();
		void			initialise(void ** p, size_t s);

	protected:
		void			grow(size_t amount);

		void *			getItemAt(int index);
		void			setItemAt(void * p, int index);
		
		size_t			getCurrentDepth() {
							return depth;
						}
		
		void			incrementCount() {
							itemCount++;
						}

		void			decrementCount() {
							itemCount--;
						}
		
	public:
		Array();
		Array(size_t initialDepth);
		
		~Array();
		
		size_t			getItemCount();
};

class Stack : public Array
{
	public:
		Stack() : Array() {}
		Stack(size_t initialDepth) : Array(initialDepth) {}
		
		void			push(void * p);
		void *			pop();
		void *			peek(int index);
};

class Queue : public Array
{
	private:
		int				headIndex;
		int				tailIndex;
		
	public:
		Queue();
		Queue(size_t initialDepth);
		
		void			addItem(void * p);
		void *			getItem();
};

#endif