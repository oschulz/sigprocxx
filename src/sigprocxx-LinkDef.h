#ifndef sigprocxx_LinkDef_h
#define sigprocxx_LinkDef_h

#ifdef __CINT__

#pragma link C++ class std::unary_function< int8_t,   int8_t>-;
#pragma link C++ class std::unary_function<uint8_t,  uint8_t>-;
#pragma link C++ class std::unary_function< int16_t,  int16_t>-;
#pragma link C++ class std::unary_function< int16_t,  int32_t>-;
#pragma link C++ class std::unary_function< int16_t,  float>-;
#pragma link C++ class std::unary_function< int16_t,  double>-;
#pragma link C++ class std::unary_function<uint16_t, uint16_t>-;
#pragma link C++ class std::unary_function< int32_t,  int32_t>-;
#pragma link C++ class std::unary_function< int32_t,  int16_t>-;
#pragma link C++ class std::unary_function< int32_t,  float>-;
#pragma link C++ class std::unary_function< int32_t,  double>-;
#pragma link C++ class std::unary_function<uint32_t, uint32_t>-;
#pragma link C++ class std::unary_function< int64_t,  int64_t>-;
#pragma link C++ class std::unary_function<uint64_t, uint64_t>-;
#pragma link C++ class std::unary_function< float,    float>-;
#pragma link C++ class std::unary_function< float,    double>-;
#pragma link C++ class std::unary_function< double,   double>-;
#pragma link C++ class std::unary_function< double,   float>-;

// src/comprehensions.h
#pragma link C++ class sigpx::FindMax<int16_t>-;
#pragma link C++ class sigpx::FindMax<int32_t>-;
#pragma link C++ class sigpx::FindMax<float>-;
#pragma link C++ class sigpx::FindMax<double>-;
#pragma link C++ class sigpx::FindMin<int16_t>-;
#pragma link C++ class sigpx::FindMin<int32_t>-;
#pragma link C++ class sigpx::FindMin<float>-;
#pragma link C++ class sigpx::FindMin<double>-;
#pragma link C++ class sigpx::FindIntersect<int16_t>-;
#pragma link C++ class sigpx::FindIntersect<int32_t>-;
#pragma link C++ class sigpx::FindIntersect<float>-;
#pragma link C++ class sigpx::FindIntersect<double>-;
#pragma link C++ class sigpx::LinearStatistics<float>-;
#pragma link C++ class sigpx::LinearStatistics<double>-;

// src/filters.h
#pragma link C++ class sigpx::DiffFilter<int8_t>-;
#pragma link C++ class sigpx::DiffFilter<int16_t>-;
#pragma link C++ class sigpx::DiffFilter<int32_t>-;
#pragma link C++ class sigpx::DiffFilter<int64_t>-;
#pragma link C++ class sigpx::DiffFilter<float>-;
#pragma link C++ class sigpx::DiffFilter<double>-;
#pragma link C++ class sigpx::SumFilter<int8_t>-;
#pragma link C++ class sigpx::SumFilter<int16_t>-;
#pragma link C++ class sigpx::SumFilter<int32_t>-;
#pragma link C++ class sigpx::SumFilter<int64_t>-;
#pragma link C++ class sigpx::SumFilter<float>-;
#pragma link C++ class sigpx::SumFilter<double>-;
#pragma link C++ class sigpx::MovingSum<int16_t, int32_t>-;
#pragma link C++ class sigpx::MovingSum<int32_t, int32_t>-;
#pragma link C++ class sigpx::MovingSum<float, float>-;
#pragma link C++ class sigpx::MovingSum<float, double>-;
#pragma link C++ class sigpx::LinCal<float>-;
#pragma link C++ class sigpx::LinCal<double>-;
#pragma link C++ class sigpx::RCFilter<float>-;
#pragma link C++ class sigpx::RCFilter<double>-;
#pragma link C++ class sigpx::CRFilter<float>-;
#pragma link C++ class sigpx::CRFilter<double>-;

// src/util.h
#pragma link C++ class sigpx::Util-;

// src/windowfcts.h
#pragma link C++ class sigpx::HammingWindow<float>;
#pragma link C++ class sigpx::HammingWindow<double>;

// src/Dither.h
#pragma link C++ class sigpx::TrigNoiseGen-;
#pragma link C++ class sigpx::Dither<int16_t, float>-;
#pragma link C++ class sigpx::Dither<int16_t, double>-;
#pragma link C++ class sigpx::Dither<int32_t, float>-;
#pragma link C++ class sigpx::Dither<int32_t, double>-;

// src/Filter.h
#pragma link C++ class sigpx::Mapper<int8_t,  int8_t>-;
#pragma link C++ class sigpx::Mapper<int16_t, int16_t>-;
#pragma link C++ class sigpx::Mapper<int16_t, int32_t>-;
#pragma link C++ class sigpx::Mapper<int16_t, float>-;
#pragma link C++ class sigpx::Mapper<int16_t, double>-;
#pragma link C++ class sigpx::Mapper<int32_t, int32_t>-;
#pragma link C++ class sigpx::Mapper<int32_t, int16_t>-;
#pragma link C++ class sigpx::Mapper<int32_t, float>-;
#pragma link C++ class sigpx::Mapper<int32_t, double>-;
#pragma link C++ class sigpx::Mapper<int64_t, int64_t>-;
#pragma link C++ class sigpx::Mapper<float,   float>-;
#pragma link C++ class sigpx::Mapper<float,   double>-;
#pragma link C++ class sigpx::Mapper<double,  double>-;
#pragma link C++ class sigpx::Mapper<double,  float>-;
#pragma link C++ class sigpx::Filter<int8_t>-;
#pragma link C++ class sigpx::Filter<int16_t>-;
#pragma link C++ class sigpx::Filter<int32_t>-;
#pragma link C++ class sigpx::Filter<int64_t>-;
#pragma link C++ class sigpx::Filter<float>-;
#pragma link C++ class sigpx::Filter<double>-;
#pragma link C++ class sigpx::Iterator<int8_t>-;
#pragma link C++ class sigpx::Iterator<int16_t>-;
#pragma link C++ class sigpx::Iterator<int32_t>-;
#pragma link C++ class sigpx::Iterator<int64_t>-;
#pragma link C++ class sigpx::Iterator<float>-;
#pragma link C++ class sigpx::Iterator<double>-;
#pragma link C++ class sigpx::RangeIterator<int32_t>-;
#pragma link C++ class sigpx::RangeIterator<float>-;
#pragma link C++ class sigpx::RangeIterator<double>-;

// src/VectorOps.h
#pragma link C++ class sigpx::VectorOps-;

// src/VectorView.h
#pragma link C++ class sigpx::VectorView<int16_t>-;
#pragma link C++ class sigpx::VectorView<int32_t>-;
#pragma link C++ class sigpx::VectorView<float>-;
#pragma link C++ class sigpx::VectorView<double>-;
#pragma link C++ typedef sigpx::VVs;
#pragma link C++ typedef sigpx::VVi;
#pragma link C++ typedef sigpx::VVf;
#pragma link C++ typedef sigpx::VVd;
#pragma link C++ class sigpx::VectorIterator<int16_t>-;
#pragma link C++ class sigpx::VectorIterator<int32_t>-;
#pragma link C++ class sigpx::VectorIterator<float>-;
#pragma link C++ class sigpx::VectorIterator<double>-;
#pragma link C++ typedef sigpx::VIs;
#pragma link C++ typedef sigpx::VIi;
#pragma link C++ typedef sigpx::VIf;
#pragma link C++ typedef sigpx::VId;
#pragma link C++ class sigpx::RevVectorIterator<int16_t>-;
#pragma link C++ class sigpx::RevVectorIterator<int32_t>-;
#pragma link C++ class sigpx::RevVectorIterator<float>-;
#pragma link C++ class sigpx::RevVectorIterator<double>-;
#pragma link C++ typedef sigpx::RVIs;
#pragma link C++ typedef sigpx::RVIi;
#pragma link C++ typedef sigpx::RVIf;
#pragma link C++ typedef sigpx::RVId;

// src/VLEncoding.h
#pragma link C++ class sigpx::VLEncoding-;

// src/ZigZagEnc.h
#pragma link C++ class sigpx::ZigZagEnc-;

#endif // __CINT__

#endif // sigprocxx_LinkDef_h
