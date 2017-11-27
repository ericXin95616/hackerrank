#include <iostream>
#include <exception>
#include <stdexcept>
#include <new>
#include <vector>
#include <cmath>

using namespace std;

class Server {
private:
	static int load;
public:
	static int compute(long long A, long long B) {
		load += 1;
		if(A < 0) {
			throw invalid_argument("A is negative");
		}
		vector<int> v(A, 0);
		int real = -1, cmplx = sqrt(-1);
		if(B == 0) throw 0;
		real = (A/B)*real;
		int ans = v.at(B);
		return real + A - B*ans;
	}
	static int getLoad() {
		return load;
	}
};
int Server::load = 0;

int main() {
	int T; cin >> T;
	while(T--) {
		long long A, B;
		cin >> A >> B;
		try {
			long long temp = Server::compute(A, B);
			cout << temp << endl;
		}
		catch (bad_alloc &err) {
			cout << "Not enough memory" << endl;
		}
		catch (exception &err) {
			cout << "Exception: " << err.what() << endl;
		}
		catch () {
			cout << "Other Exception" << endl;
		}
		}
	cout << Server::getLoad() << endl;
	return 0;
}



