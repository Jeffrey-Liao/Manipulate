#ifndef LINKLIST_H
#define LINKLIST_H
#include "List.h"
#include"LinkNode.h"
namespace liaoUtil
{
	//=std::list
	DYNAMIC
	class LinkList :public List<T>
	{
		using List = List<T>;
	protected:
		list<T> dataSource;
	public:
		LinkList()
			:List()
		{}
		constexpr LinkList(size_t _size)
			:List(_size)
		{}
		constexpr LinkList(const List& obj)
			:List(obj)
		{}
		constexpr LinkList(const vector<T>& obj)
		{
			this->StdToStd(obj);
		}
		constexpr LinkList(const initializer_list<T> ini)
		{
			this->StdToStd( ini);
		}
		constexpr LinkList(const list<T>& obj)
		{
			dataSource = obj;
		}
	protected:
		void allocate(const size_t _size) override
		{
			dataSource.resize(dataSource.size() + _size);
		}
		void newValue(const T& value)override
		{
			dataSource.push_back(value);
		}
		void newValue(const T&& value)
		{
			dataSource.push_back(value);
		}
		void newValue(const List& obj)
		{
			for (int n = 0; n < obj.size(); ++n)
				newValue(obj[n]);
		}
		size_t inner_findIndex(const T& value)const 
		{
			auto itor = dataSource.begin();
			int n = 0;
			while (itor != dataSource.end())
			{
				if (*itor == value)
					return n;
				++itor;
				++n;
			}
			return -1;
		}
		list<T>::iterator iterate(size_t pos)
		{
			int end = 0;
			auto itor = dataSource.begin();
			if (pos > (dataSource.size()/2))
				itor = dataSource.end(),end = dataSource.size()-pos;
			else
				itor = dataSource.begin(),end = pos;
			for (int n = 0; n < end&&pos>0; ++n)
			{
				if (pos > (dataSource.size() / 2))
					itor--;
				else
					itor++;
			}
			return itor;
		}
		constexpr bool validPos(Index pos)const override
		{
			return pos < dataSource.size()&&pos>=0;
		}
		constexpr void free() override
		{
			dataSource.clear();
		}
	public:
		constexpr virtual string classID() const noexcept
		{
			return "LinkList";
		}
		constexpr size_t size() const override
		{
			return dataSource.size();
		}
		constexpr bool isEmpty() const override
		{
			return dataSource.empty();
		}
		constexpr T& first()
		{
			this->emptyListCheck("first()");
			return *dataSource.begin();
		}
		constexpr const T& first()const override
		{
			this->emptyListCheck("first()");
			return *dataSource.begin();
		}
		constexpr T& last() override
		{
			this->emptyListCheck("last()");
			return *(--dataSource.end());
		}
		constexpr const T& last()const override
		{
			this->emptyListCheck("last()");
			return *(--dataSource.end());
		}

		virtual T& add(const T& data)override
		{
			newValue(data);
			return *(--dataSource.end());
		}
		virtual T& add(const List& obj) override
		{
			newValue(obj);
			return *iterate(dataSource.size()-obj.size());
		}
		virtual T& add(int number, T& value)
		{
			for (int n = 0; n < number; ++n)
				newValue(value);
			return *iterate(dataSource.size()-number);
		}
		virtual T& add(const vector<T>& vec)
		{
			this->StdToStd(vec);
			return *iterate(dataSource.size() - vec.size());
		}
		virtual T& add(const list<T>& ls)
		{
			this->StdToStd( ls);
			return *iterate(dataSource.size() - ls.size());
		}
		virtual T& add(const initializer_list<T>& ini)
		{
			this->StdToStd(ini);
			return* iterate(dataSource.size() - ini.size());
		}
		virtual T& add(const T* arr, const int size)
		{
			for (int n = 0; n < size; ++n)
			{
				newValue(arr[n]);
			}
			return *iterate(dataSource.size() - size );
		}
		virtual T& add(T&& value)
		{
			newValue(value);
			return *(--dataSource.end());
		}
		virtual T& add(const int number, T&& value) override
		{
			newValue(value);
			return * (--dataSource.end());
		}
		void remove(const Index pos)
		{
			this->emptyListCheck("remove(Index)");
			this->outRangeCheck(pos,"remove(Index)");
			dataSource.erase(iterate(pos));
		}
		void remove(const Index start, const Index end)
		{
			this->emptyListCheck("remove(Index,Index)");
			this->validIntervalCheck(start, end,"remove(Index,Index)");
			auto itor1 = dataSource.begin(), itor2 = dataSource.begin(), itor = dataSource.begin();
			for (int n = 0; n < dataSource.size(); ++n, itor++)
			{
				if (n == start)
					itor1 = itor;
				if (n == end)
				{
					itor2 = itor;
					break;
				}
			}
			dataSource.erase(itor1, itor2);
		}
		void remove(const T& data)
		{
			this->emptyListCheck("remove(T&)");
			dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), data));
		}
		void remove(T&& value)override
		{
			this->emptyListCheck("remove(T&&)");
			dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), value));
		}
		void removeAll(const T& data)
		{
			this->emptyListCheck("removeAll(T&)");
			dataSource.remove(data);
		}
		void remove(const initializer_list<T>& ini)
		{
			this->emptyListCheck("removeAll(initializer_list<T>&)");
			for (auto& var : ini)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), var));
		}
		void remove(const List& obj)
		{
			this->emptyListCheck("removeAll(List&)");
			for(int n =0;n<obj.size();++n)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), obj[n]));
		}
		void remove(const vector<T>& vec)
		{
			this->emptyListCheck("removeAll(vector<T>&)");
			for (auto& var : vec)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), var));
		}
		void remove(const list<T>& ls) 
		{
			this->emptyListCheck("removeAll(list<T>&)");
			for (auto& var : ls)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), var));
		}
		void remove(const T* arr, const int size)
		{
			this->emptyListCheck("removeAll(T*,int)");
			for (int n = 0; n < size; ++n)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), arr[n]));
		}
		virtual T& insert(const Index pos, const T& value)
		{
			this->outRangeCheck(pos,"insert(Index,T&)");
			return *dataSource.insert(iterate(pos), value);
		}
		virtual T& insert(const Index pos, T&& value)override
		{
			this->outRangeCheck(pos, "insert(Index,T&&)");
			return *dataSource.insert(iterate(pos), value);
		}
		virtual T& insert(const Index pos, const List& list)
		{
			this->outRangeCheck(pos, "insert(Index,List&)");
			for (int n = 0; n < list.size(); ++n)
				dataSource.insert(iterate(pos+n), list[n]);
			return *iterate(pos);
		}
		virtual T& insert(const Index pos, const vector<T>& vec)
		{
			this->outRangeCheck(pos, "insert(Index,vector<T>&)");
			dataSource.insert(iterate(pos), vec.begin(), vec.end());
			return *iterate(pos);
		}
		virtual T& insert(const Index pos, const list<T>& list)
		{
			this->outRangeCheck(pos, "insert(Index,vector<T>&)");
			dataSource.insert(iterate(pos), list.begin(), list.end());
			return *iterate(pos);
		}
		virtual T& insert(const Index pos, const initializer_list<T>& ini)
		{
			this->outRangeCheck(pos, "insert(Index,vector<T>&)");
			dataSource.insert(iterate(pos),ini.begin(), ini.end());
			return *iterate(pos);
		}
		constexpr T& get(const Index index)
		{
			this->outRangeCheck(index,"get(Index)");
			return *iterate(index);
		}
		size_t indexOf(const T& data)const override
		{
			return inner_findIndex(data);
		}
		constexpr void clear()
		{
			dataSource.clear();
		}
		constexpr bool equals(const List& obj) const
		{
			if (obj.size() != dataSource.size())
				return false;
			auto itor = dataSource.begin();
			for (int n = 0; n < obj.size(); ++n)
			{
				if (*itor != obj[n])
					return false;
			}
			return true;
		}
		constexpr bool equals(const vector<T>& vec) const
		{
			return std::equal(dataSource.begin(), dataSource.end(), vec.begin());
		}
		constexpr bool equals(const list<T>& list)const
		{
			return dataSource == list;
		}
		constexpr bool equals(const initializer_list<T>& ini)const
		{
			return std::equal(dataSource.begin(), dataSource.end(), ini.begin());
		}
		constexpr bool equals(const T* arr, const int size)const
		{
			if (dataSource.size() != size)
				return false;
			auto itor = dataSource.begin();
			for (int n = 0; n < size; ++n)
			{
				if (arr[n] != *itor)
					return false;
			}
			return true;
		}
		constexpr virtual void assign(const vector<T>& vec)
		{
			dataSource.resize(vec.size());
			std::copy(vec.begin(), vec.end(), dataSource.begin());
		}
		constexpr virtual void assign(const list<T>& list)
		{
			dataSource = list;
		}
		constexpr virtual void assign(const initializer_list<T>& ini)
		{
			dataSource.resize(ini.size());
			std::copy(ini.begin(), ini.end(), dataSource.begin());
		}
		vector<T> toVector() const
		{
			vector temp(dataSource.begin(), dataSource.end());
			return std::move(temp);
		}
		constexpr bool contains(const T&& value)const
		{
			return std::find(dataSource.begin(), dataSource.end(), value) != dataSource.end();
		}
		constexpr bool contains(const T& value)const
		{
			return std::find(dataSource.begin(), dataSource.end(), value) != dataSource.end();
		}
		constexpr bool contains(const List& obj)const
		{
			for (int n = 0; n < obj.size(); ++n)
			{
				for (auto& var : dataSource)
					if (var != obj[n])
						return false;
			}
			return true;
		}
		constexpr bool contains(const vector<T>& vec)const
		{
			for (int n = 0; n < vec.size(); ++n)
			{
				for (auto& var : dataSource)
					if (var != vec[n])
						return false;
			}
			return true;
		}
		constexpr bool contains(const list<T>& list)const
		{
			for (auto& var2 : list)
			{
				for (auto& var : dataSource)
					if (var != var2)
						return false;
			}
			return true;
		}
		constexpr bool contains(const initializer_list<T>& ini)const
		{
			for (auto& var2 : ini)
			{
				for (auto& var : dataSource)
					if (var != var2)
						return false;
			}
			return true;
		}
		void sort(void(*sortFunc)(List& _this) = NULL)override
		{
			this->emptyListCheck("sort(sortFunc*)");
			if (sortFunc != NULL)
				sortFunc(*this);
			else
				dataSource.sort();
		}

		void apply(void(*operation)(T& value)) override
		{
			for (auto& var : dataSource)
				operation(var);
		}
		constexpr size_t count(const T& data)const override
		{
			return std::count(dataSource.begin(), dataSource.end(), data);
		}
		void subList(List& destination, const  Index start, const Index end) override
		{
			this->emptyListCheck("subList(List&)");
			this->validIntervalCheck(start, end, "subList(List&)");
			for (int n = start; n <= end; ++n)
				destination.add(*iterate(n));
		}
		constexpr void copyFrom(const List& obj) override
		{
			dataSource.resize(obj.size());
			for (int n = 0; n < size(); ++n)
				*iterate(n) = obj[n];
		}
		constexpr void copyTo(List& obj) override
		{
			obj.resize(size());
			for (int n = 0; n < size(); ++n)
				obj[n] = *iterate(n);
		}
		constexpr virtual void set(const Index pos, const T& value)
		{
			this->outRangeCheck(pos, "set(Index,T&)");
			*iterate(pos) = value;
		}
		constexpr virtual void swap(const Index pos1, const Index pos2)
		{
			this->outRangeCheck(pos1, "swap(Index,Index)");
			this->outRangeCheck(pos2, "swap(Index,Index)");
			std::swap(*iterate(pos1), *iterate(pos2));
		}
		constexpr void reverse()
		{
			std::reverse(dataSource.begin(), dataSource.end());
		}
		constexpr virtual void resize(const Index newSize)
		{
			allocate(newSize);
		}
		virtual ~LinkList() override
		{
			dataSource.clear();
		}
	};
	DYNAMIC
		//
	class LiaoLinkList:public List<T>
	{
		using LinkNode = LinkNode<T>;
		using List = List<T>;
		LinkNode* head;
		LinkNode* temp;
		size_t _size;
	private:
		void quickSort()
		{

		}
		constexpr LinkNode* end()
		{
			if (head == NULL)
				return NULL;
			else if (head->isSingle())
				return head;
			else
				return &head->prev();
		}
		void newValue(const T& value)
		{
			++_size;
			LinkNode* ptr = end();
			if (ptr)
				ptr->link(*new LinkNode(ptr, head, value));
			else
				head = new LinkNode(value),head->link(*head);
		}
		void newValue(T&& value)
		{
			++_size;
			LinkNode* ptr = end();
			if (ptr)
				ptr->link(*new LinkNode(ptr, head, value));
			else
				head = new LinkNode(value);
		}
		void newValue()
		{
			++_size;
			LinkNode* ptr = end();
			if (ptr)
				ptr->link(*new LinkNode(ptr, head));
			else
				head = new LinkNode();
		}
		constexpr void allocate(const size_t size)override
		{
			for (int n = 0; n < size; ++n)
				newValue();
		}
		constexpr bool validPos(Index pos)const
		{
			return pos<_size && pos >0;
		}
		LinkNode* iterate(int pos)
		{
			static int lastPos = 0;
			char offset = 0;
			if (temp ==NULL|| pos < lastPos - pos)
				temp = head, lastPos = 0;
			else if (_size - pos < pos - lastPos)
				temp = end(), lastPos = _size-1;
			offset = pos > lastPos ? 1 : -1;
			while(lastPos!=pos&&temp!=NULL)
			{
				temp = offset>0? &temp->next():&temp->prev();
				lastPos += offset;
			}
			return temp;
		}
		const LinkNode* iterate(int pos) const 
		{
			static int lastPos = 0;
			char offset = 0;
			LinkNode* tempLocal = head;
			if (temp != NULL)
				tempLocal = temp;
			
		}
		LinkNode* inner_find(const T& value)
		{
			LinkNode* stop = head;
			do
			{
				if (stop->value() == value)
					return stop;
				stop = &stop->next();
			} while (stop != head);
			return NULL;
		}
		const LinkNode* inner_findConst(const T& value) const
		{
			if (head != NULL)
			{
				LinkNode* stop = head;
				do
				{
					if (stop->value() == value)
						return stop;
					stop = &stop->next();
				} while (stop != head);
			}
			return NULL;
		}
		constexpr void free()
		{
			if (!isEmpty())
			{
				LinkNode* del = head;
				for (int n = 0; n < _size; ++n)
				{
					head = &head->next();
					delete del;
					del = head;
				}
				head = NULL;
				_size = 0;
			}
		}
		template<class Container>
		LinkNode* addContainer(LinkNode* pos, Container& obj)
		{
			LinkNode* temp=end();
			for (int n = 0; n < obj.size(); ++n)
			{
				newValue(obj[n]);
				if (n == 0)
					temp = end();
			}
			return temp;
		}
		template<class Container>
		LinkNode* addStdContainer(LinkNode* pos, Container& obj)
		{
			LinkNode* temp;
			for (auto& data:obj)
			{
				newValue(data);
			}
			temp = iterate(_size-obj.size());
			return temp;
		}
		template<class Container>
		void removeStd(Container& obj)
		{
			for (auto& var : obj)
			{
				remove(var);
			}
		}
	public:
		LiaoLinkList()
			:List(), head(NULL), _size{},temp(NULL)
		{}
		LiaoLinkList(size_t size)
			:List(size),head(NULL), _size{size}, temp(NULL)
		{}
		LiaoLinkList(const List& obj)
			:List(obj),head(NULL), _size{}, temp(NULL)
		{}
		LiaoLinkList(vector<T>& vec)
			:temp(NULL)
		{
			this->StdToStd(vec);
		}
		LiaoLinkList(list<T> ls)
		{
			this->StdToStd(ls);
		}
		LiaoLinkList(initializer_list<T>& ini)
			:temp(NULL)
		{
			this->StdToStd(ini);
		}
		constexpr string classID()const override
		{
			return "LiaoLinkList";
		}
		constexpr size_t size()const
		{
			return _size;
		}
		constexpr bool isEmpty()const 
		{
			return _size == 0 || head == NULL;
		}
		constexpr T& first()
		{
			this->emptyListCheck("first()");
			return head->value();
		}
		constexpr T& last()
		{
			this->emptyListCheck("last()");
			return head->prev().value();
		}
		constexpr const T& first()const 
		{
			this->emptyListCheck("first()");
			return head->value();
		}
		constexpr const T& last()const 
		{
			this->emptyListCheck("last()");
			return head->prev().value();
		}
		T& add(T&& value)
		{
			newValue(value);
			return end()->value();
		}
		T& add(const T& value)
		{
			newValue(value);
			return end()->value();
		}
		T& add(const List& obj)
		{
			return addContainer(end(), obj)->value();
		}
		T& add(int number, T&& value)
		{
			LinkNode* temp=end();
			for (int n = 0; n < number; ++n)
			{
				newValue(value);
				if (n == 0)
					temp = end();
			}
			return temp->value();
		}
		T& add(int number, T& value)
		{
			LinkNode* temp=end();
			for (int n = 0; n < number; ++n)
			{
				newValue(value);
				if (n == 0)
					temp = end();
			}
			return temp->value();
		}
		T& add(const vector<T>& vec)
		{
			return addStdContainer(end(), vec)->value();
		}
		T& add(const list<T>& ls)
		{
			return addStdContainer(end(), ls)->value();
		}
		T& add(const initializer_list<T>& ini)
		{
			return addStdContainer(end(), ini)->value();
		}
		T& add(const T* arr, int size)
		{
			if (size == 0)
				return end()->value();
			LinkNode* temp=NULL;
			for (int n = 0; n < size; ++n)
			{
				newValue(arr[n]);
				if (n == 0)
					temp = end();
			}
			return temp->value();
		}
		void remove(const Index pos)
		{
			this->emptyListCheck("remove(Index)");
			this->outRangeCheck(pos, "remove(Index)");
			delete iterate(pos);
		}
		void remove(const Index start, const Index end)
		{
			this->emptyListCheck("remove(Index,Index)");
			this->validIntervalCheck(start, end, "remove(Index,Index)");
			for (Index n = start; n <= end; n++)
				remove(n);
		}
		void remove(const T& data)
		{
			this->emptyListCheck("remove(T&)");
			LinkNode* local = inner_find(data);
			if (local)
				delete local;
		}
		void remove(T&& data)
		{
			this->emptyListCheck("remove(T&&)");
			remove(data);
		}
		void remove(const List& obj)
		{
			this->emptyListCheck("remove(List&)");
			for (int n = 0; n < obj.size(); ++n)
				remove(obj[n]);
		}
		void remove(const initializer_list<T>& ini)
		{
			this->emptyListCheck("remove(initializer_list<T>&)");
			removeStd(ini);
		}
		void remove(const vector<T>& ini)
		{
			this->emptyListCheck("remove(vector<T>&)");
			removeStd(ini);
		}
		void remove(const list<T>& ini)
		{
			this->emptyListCheck("remove(list<T>&)");
			removeStd(ini);
		}
		void remove(T* arr, int size)
		{
			this->emptyListCheck("remove(T*,int)");
			for (int n = 0; n < size; ++n)
				remove(arr[n]);
		}
		void removeAll(const T& value)
		{
			LinkNode* node = head;
			do
			{
				node = &node->next();
				if (node->prev().value() == value)
					delete &node->prev();
			} while(node != head);
		}
		T& insert(Index pos, T&& value)
		{
			this->outRangeCheck(pos, "insert(Index,T&&)");
			return iterate(pos)->linkPrev(value).value();
		}
		T& insert(Index pos, const T& value)
		{
			this->outRangeCheck(pos, "insert(Index,T&)");
			return iterate(pos)->linkPrev(value).value();
		}
		T& insert(Index pos, const List& list)
		{
			this->outRangeCheck(pos, "insert(Index, List&)");
			T* firstEle = &end()->value();
			for (int n = pos; n < list.size(); ++n)
			{
				insert(n, list[n]);
				if (n == 0)
					firstEle = &temp->value();
			}
			return *firstEle;
		}
		T& insert(Index pos, const vector<T>& vec)
		{
			this->outRangeCheck(pos, "insert(Index, vector<T>&)");
			T* firstEle = NULL;
			for (auto& var : vec)
			{
				insert(pos++, var);
				if (firstEle == NULL)
					firstEle = &temp->value();
			}
			return *firstEle;
		}
		//在指定位置插入一个list
		T& insert(Index pos, const list<T>& list)
		{
			this->outRangeCheck(pos, "insert(Index, list<T>&)");
			T* firstEle = NULL;
			for (auto& var : list)
			{
				insert(pos++, var);
				if (firstEle == NULL)
					firstEle = &temp->value();
			}
			return *firstEle;
		}
		//在指定位置插入一个initializer
		T& insert(Index pos, const initializer_list<T>& ini)
		{
			this->outRangeCheck(pos, "insert(Index, list<T>&)");
			T* firstEle = NULL;
			for (auto& var : ini)
			{
				insert(pos++, var);
				if (firstEle == NULL)
					firstEle = &temp->value();
			}
			return *firstEle;
		}
		T& get(Index index)
		{
			this->emptyListCheck("get(Index)");
			this->outRangeCheck(index, "get(Index)");
			return iterate(index)->value();
		}
		const T& get(Index index) const 
		{
			this->emptyListCheck("get(Index)");
			this->outRangeCheck(index, "get(Index)");
			return iterate(index)->value();
		}
		size_t indexOf(const T& data)const 
		{
			this->emptyListCheck("indexOf(T&)");
			LinkNode* localNode = head;
			size_t pos = 0;
			do
			{
				if (localNode->value() == data)
					return pos;
				pos++;
			} while (localNode != head);
			return -1;
		}
		void clear()
		{
			head->unlinkAll();
			delete head;
			head = NULL;
			_size = 0;
		}
		bool equals(const List& obj) const
		{
			if (_size != obj.size())
				return false;
			else
			{
				LinkNode* temp = head;
				for (int n = 0; n < _size; ++n)
				{
					if (inner_findConst(obj[n]) == NULL)
						return false;
				}
				return true;
			}
		}
		bool equals(const vector<T>& vec) const
		{
			if (_size != vec.size())
				return false;
			else
			{
				LinkNode* temp = head;
				for(auto& var: vec)
				{
					if (inner_findConst(var) == NULL)
						return false;
				}
				return true;
			}
		}
		bool equals(const list<T>& list)const
		{
			if (_size != list.size())
				return false;
			else
			{
				LinkNode* temp = head;
				for (auto& var : list)
				{
					if (inner_findConst(var) == NULL)
						return false;
				}
				return true;
			}
		}
		bool equals(const initializer_list<T>& ini)const
		{
			if (_size != ini.size())
				return false;
			else
			{
				LinkNode* temp = head;
				for (auto& var : ini)
				{
					if (inner_findConst(var) == NULL)
						return false;
				}
				return true;
			}
		}
		bool equals(T* arr, int size)const
		{
			if (_size != size)
				return false;
			else
			{
				LinkNode* temp = head;
				for (int n = 0; n < _size; ++n)
				{
					if (inner_findConst(arr[n]) == NULL)
						return false;
				}
				return true;
			}
		}
		vector<T> toVector()const
		{
			vector<T> vec;
			LinkNode* node=  head;
			do
			{
				vec.push_back(node->value());
			} while (node != head);
			return vec;
		}
		bool contains(const T&& value)const
		{
			return inner_findConst(value) != NULL;
		}
		bool contains(const T& value)const
		{
			return inner_findConst(value) != NULL;
		}
		bool contains(const List& obj)const
		{
			for (int n = 0; n < obj.size(); ++n)
			{
				if (!contains(obj[n]))
					return false;
			}
			return true;
		}
		bool contains(const vector<T>& vec)const
		{
			for (auto& var : vec)
			{
				if(!contains(var))
					return false;
			}
			return true;
		}
		bool contains(const list<T>& list)const
		{
			for (auto& var : list)
			{
				if (!contains(var))
					return false;
			}
			return true;
		}
		bool contains(const initializer_list<T>& ini)const
		{
			for (auto& var : ini)
			{
				if (!contains(var))
					return false;
			}
			return true;
		}
		void assign(const vector<T>& vec)
		{
			this->resize(vec.size());
			LinkNode* node = head;
			for (auto var:vec)
			{
				node->assign(var);
				node = &node->next();
			}
		}
		//将list覆写到当前容器
		void assign(const list<T>& list)
		{
			this->resize(list.size());
			LinkNode* node = head;
			for (auto var : list)
			{
				node->assign(var);
				node = &node->next();
			}
		}
		//将initializer覆写到当前容器
		void assign(const initializer_list<T>& ini)
		{
			this->resize(ini.size());
			LinkNode* node = head;
			for (auto var : ini)
			{
				node->assign(var);
				node = &node->next();
			}
		}
		void sort(void(*sortFunc)(List& _this) = NULL)
		{
			this->emptyListCheck("sort(operation)");
			if (sortFunc == NULL)
				this->quickSort();
			else
				sortFunc(*this);
		}
		void apply(void(*operation)(T& value))
		{
			this->emptyListCheck("apply(operation)");
			LinkNode* temp = head;
			do
			{
				operation(temp->value());
				temp = &temp->next();
			} while (temp != head);
		}
		size_t count(const T& data)const
		{
			size_t cnt = 0;
			LinkNode* temp = head;
			do
			{
				if (temp->value() == data)
					cnt++;
				temp = &temp->next();
			} while (temp != head);
			return cnt;
		}
		void subList(List& destination, const Index start, const Index end)
		{
			this->validIntervalCheck(start, end, "subList(List&,Index,Index)");
			destination.resize(start-end);
			for (int n = start; n < end; ++n)
			{
				auto node=iterate(n);
				destination.add(node->value());
			}
		}
		void copyFrom(const List& obj)
		{
			this->resize(obj.size());
			for (int n = 0; n < obj.size(); ++n)
			{
				get(n) = obj[n];
			}
		}
		void copyTo(List& obj)
		{
			obj.resize(this->size());
			for(int n =0;n<this->size();++n)
			{
				get(n) = obj[n];
			}
		}
		void set(const Index pos, const T& value)
		{
			this->outRangeCheck(pos, "set(Index, T&)");
			get(pos) = value;
		}
		void swap(Index pos, Index pos2)
		{
			this->outRangeCheck(pos, "swap(Index, Index)");
			this->outRangeCheck(pos2, "swap(Index, Index)");
			iterate(pos)->swap(*iterate(pos2));
		}
		constexpr void reverse()
		{
			LinkNode* node = head;
			do
			{
				node->exchange();
				node = &node->next();
			} while (node != head);
			head = &head->next();
		}
		void resize(const size_t size)
		{
			if (size != 0)
			{
				if (size > _size)
					this->allocate(size - _size);
				else
					iterate(size - 1)->unlinkAll();
			}
		}
		~LiaoLinkList()
		{
			free();
		}
	};
}

#endif