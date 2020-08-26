#ifndef TMN_NMSPC_H
#define TMN_NMSPC_H

namespace tmn{
	//typedef for less includes
	typedef unsigned long long size_t;
	/* typedef unsigned char u8; */
	/* typedef unsigned short u16; */
	/* typedef unsigned int u32; */
	/* typedef unsigned long u64; */
	/* typedef char s8; */
	/* typedef short s16; */
	/* typedef int s32; */
	/* typedef long s64; */

	//a - factor
	//c - increment
	//m - modulo this (max number + 1)
	//internal state has to be passed in to remain constexpr
	template <int a, int c, int m>
	struct LinearCongruentialGenerator{
		constexpr int operator()(int internal_state){
			internal_state = (a * internal_state + c ) % m;
			return internal_state;
		}
		constexpr int max(){
			return m-1;
		}
		constexpr int min(){
			return 0;
		}
		typedef int result_type;
	};
	template<int a, int b, int m>
	using LCG = LinearCongruentialGenerator<a, b, m>;

	template <typename T>
	constexpr void swap(T &a, T &b){
		T temp = a;
		a = b;
		b = temp;
	}

	template <typename T, size_t n>
	struct array{
		T arr[n];

		constexpr T &operator[](size_t index){
			return arr[index];
		}
		constexpr T operator[](size_t index) const{
			return arr[index];
		}
		constexpr T &front(){
			return arr[0];
		}
		constexpr T front() const{
			return arr[0];
		}
		constexpr T &back(){
			return arr[n-1];
		}
		constexpr T back() const{
			return arr[n-1];
		}
		constexpr size_t size() const{
			return n;
		}
		constexpr T *data(){
			return &front();
		}
		constexpr void *data_notype(){
			return static_cast<void*>(&front());
		}
	};

	template <int n>
	constexpr tmn::array<int, n> shuffle_n(){
		tmn::array<int, n> arr = {0};
		for(int i = 0; i < n; i++)
			arr[i] = i;

		int lcg_state = 0;
		tmn::LCG<13 * 17, 19, n> lcg;

		for(int i = n*n; i > 0; i--){
			lcg_state = lcg(lcg_state);
			int &loc = lcg_state;
			int next = (loc + 1) % n;
			tmn::swap(arr[loc], arr.back());
			tmn::swap(arr[loc], arr[next]);
		}
		return arr;
	}
}

#endif

