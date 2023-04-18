


int code[ 3 ][ 3 ] = {{3051,4036,4012},{3,3,3},{3,3,3}};
int lenr[ 3 ][ 3 ] = {{24,24,24},{3,3,3},{3,3,3}};
int protr[ 3 ][ 3 ] = {{3051,4036,4012},{3,3,3},{3,3,3}};





template <class T, size_t N> constexpr size_t len(const T(&)[N]) { return N; }
