#include <stdlib.h>

#include "exception.h"
#include "stack.h"

Array::Array(size_t initialDepth)
{
	array = (void **)malloc((sizeof(void *)) * initialDepth);

	if (array == NULL) {
		throw new Exception(
					ERR_MALLOC,
					"Failed to allocate memory",
					__FILE__,
					"Array",
					"Array()",
					__LINE__);
	}

	depth = initialDepth;
	itemCount = 0;

	initialise();
}

Array::Array() : Array(DEFAULT_DEPTH)
{
}

Array::~Array()
{
	int		i;
	void *	p;

	for (i = 0;i < getItemCount();i++) {
		p = getItemAt(i);
		free(p);
	}

	free(array);
}

void Array::initialise()
{
	initialise(array, depth);
}

void Array::initialise(void ** p, size_t s)
{
	int		i;

	for (i = 0;i < (int)s;i++) {
		p[i] = NULL;
	}
}

void Array::grow(size_t amount)
{
	void **		newArray;
	size_t		newDepth;
	int			i;

	newDepth = depth + amount;

	newArray = (void **)malloc(sizeof(void *) * newDepth);

	initialise(newArray, newDepth);

	for (i = 0;i < (int)depth;i++) {
		newArray[i] = array[i];
	}

	free(array);

	array = newArray;
	depth = newDepth;
}

size_t Array::getItemCount()
{
	return itemCount;
}

void * Array::getItemAt(int index)
{
	void * p;

	if (index > (int)depth) {
		throw new Exception(
					ERR_INDEX_OUT_OF_RANGE,
					"Attempt to access item beyond end of array",
					__FILE__,
					"Array",
					"getItemAt()",
					__LINE__);
	}

	p = array[index];

	return p;
}

void Array::setItemAt(void * p, int index)
{
	if (index > (int)depth) {
		throw new Exception(
					ERR_INDEX_OUT_OF_RANGE,
					"Attempt to set item beyond end of array",
					__FILE__,
					"Array",
					"setItemAt()",
					__LINE__);
	}

	array[index] = p;
}


void * Stack::pop()
{
	void * p;

	if (getItemCount() > 0) {
		p = getItemAt((int)getItemCount() - 1);

		decrementCount();
	}
	else {
		p = NULL;
	}

	return p;
}

void * Stack::peek(int index)
{
	void * p;

	if (getItemCount() > 0) {
		p = getItemAt(index);
	}
	else {
		p = NULL;
	}

	return p;
}

void Stack::push(void * p)
{
	if (p != NULL) {
		if (getItemCount() == getCurrentDepth()) {
			grow(DEFAULT_DEPTH);
		}

		setItemAt(p, (int)getItemCount());

		incrementCount();
	}
}


Queue::Queue() : Array()
{
	headIndex = 0;
	tailIndex = 0;
}

Queue::Queue(size_t initialDepth) : Array(initialDepth)
{
	headIndex = 0;
	tailIndex = 0;
}

void * Queue::getItem()
{
	void * p;

	if (getItemCount() > 0) {
		p = getItemAt(headIndex++);

		decrementCount();
	}
	else {
		p = NULL;
	}

	return p;
}

void Queue::addItem(void * p)
{
	if (p != NULL) {
		if (getItemCount() == getCurrentDepth()) {
			grow(DEFAULT_DEPTH);
		}

		setItemAt(p, tailIndex++);

		if (tailIndex == (int)getCurrentDepth()) {
			if (headIndex > 0) {
				tailIndex = 0;
			}
			else {
				throw new Exception(
							ERR_ARRAY_OVERFLOW,
							"Queue is full, should not be here",
							__FILE__,
							"Queue",
							"addItem()",
							__LINE__);
			}
		}

		incrementCount();
	}
}
