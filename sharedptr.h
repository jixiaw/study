
template<class T>
class SharedPtr{
public:
    SharedPtr() :ptr_(NULL), count_(new int(0)){}
    SharedPtr(T* ptr) {
        if (ptr) {
            ptr_ = ptr;
            count_ = new int(1);
        }
    }
    ~SharedPtr() {
        if (--(*count_) == 0) {
            delete ptr_;
            delete count_;
        }
    }
    SharedPtr(SharedPtr<T>& p) {
        ptr_ = p.ptr_;
        count_ = p.count_;
        (*count_)++;
    }
    T* operator->() { return ptr_; }
    T& operator*() { return *ptr_; }
    SharedPtr<T>& operator=(SharedPtr<T>& p) {
        if (!ptr_){
            if (--(*count_) == 0) {
                delete ptr_;
                delete count_;
            }
        }
        ptr_ = p.ptr_;
        count_ = p.count_;
        ++(*count_);
    }

    int GetCount() { return *count_; }
    T* Get() { return ptr_; }

private:
    int* count_;
    T* ptr_;
};