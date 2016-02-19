#include "TMessage.h"
#include "TH1.h"
#include "TFile.h"
#include "simple.h"
#include "hits_generated.h"
#include "digis_generated.h"
#include <msgpack.hpp>
#include "event_types.h"
#include "MPackEDM.h"
#include "TSystem.h"
#include "thrift/protocol/TBinaryProtocol.h"
#include "thrift/protocol/TCompactProtocol.h"
#include "thrift/protocol/TJSONProtocol.h"
#include "thrift/transport/TBufferTransports.h"


#include <iostream>
#include <sstream>

constexpr int SIZE = 30;

int
main() {
  Digi *d = new Digi();
  Hit *h = new Hit();
  auto root_digis = new ArrayOfDigi();
  root_digis->digis.resize(SIZE);
  auto root_hits = new ArrayOfHits();
  root_hits->hits.resize(SIZE);
{
  std::cerr << "Digis - packed in memory: " << SIZE*3*4 + SIZE*2*8 << std::endl;
  std::cerr << "Hits - packed in memory: " << SIZE*2*4 + SIZE*8*8 << std::endl;
}
{
  TMessage message(kMESS_OBJECT);
  TMessage messageStruct(kMESS_OBJECT);
  TMessage messageSingle(kMESS_OBJECT);
  message.WriteObject(root_digis);
  messageStruct.WriteObject(new StructureOfDigis(SIZE));
  messageSingle.WriteObject(d);
  std::cerr << "Digis TMessage - Single: " << messageSingle.Length() << ", AoS: " << message.Length()
            << ", SoA:" << messageStruct.Length() << std::endl;
}
{
  TMessage message(kMESS_OBJECT);
  TMessage messageStruct(kMESS_OBJECT);
  TMessage messageSingle(kMESS_OBJECT);
  message.WriteObject(root_hits);
  messageStruct.WriteObject(new StructureOfHits(SIZE));
  messageSingle.WriteObject(h);
  std::cerr << "Hits TMessage - Single: " << messageSingle.Length() << ", AoS: " << message.Length() 
            << ", SoA:" << messageStruct.Length() << std::endl;
}
{
  flatbuffers::FlatBufferBuilder builder;
  flatbuffers::Offset<FBDigi> digi[SIZE];
  for (size_t i = 0; i < SIZE; ++i)
  {
    FBDigiBuilder elementBuilder(builder);
    elementBuilder.add_a(rand());
    elementBuilder.add_b(rand());
    elementBuilder.add_c(rand());
    elementBuilder.add_d(rand());
    elementBuilder.add_e(rand());
    digi[i] = elementBuilder.Finish();
  }
  auto vec = builder.CreateVector(digi, SIZE);
  auto container = CreateFBDigis(builder, vec);
  FinishFBDigisBuffer(builder, container);
  std::cerr << "Digis Flatbuffer - " << builder.GetSize() << std::endl;
}
{
  flatbuffers::FlatBufferBuilder builder;
  flatbuffers::Offset<FBHit> hits[SIZE];
  for (size_t i = 0; i < SIZE; ++i)
  {
    FBHitBuilder fbhitBuilder(builder);
    fbhitBuilder.add_a(rand());
    fbhitBuilder.add_b(rand());
    fbhitBuilder.add_c(rand());
    fbhitBuilder.add_d(rand());
    fbhitBuilder.add_e(rand());
    fbhitBuilder.add_f(rand());
    fbhitBuilder.add_g(rand());
    fbhitBuilder.add_h(rand());
    hits[i] = fbhitBuilder.Finish();
  }
  auto vec = builder.CreateVector(hits, SIZE);
  auto container = CreateFBHits(builder, vec);
  FinishFBHitsBuffer(builder, container);
  std::cerr << "Hits Flatbuffer - " << builder.GetSize() << std::endl;
}
{
    /* msgpack::sbuffer is a simple buffer implementation. */
    std::vector<MPDigi> vec(SIZE);
    for(int i = 0; i < SIZE; ++i)
    {
      vec[i].a = rand();
      vec[i].b = rand();
      vec[i].c = rand();
      vec[i].d = rand();
      vec[i].e = rand();
    }
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, vec);
    std::cerr << "Digis msgpack: " << sbuf.size() << std::endl;
}
{
    /* msgpack::sbuffer is a simple buffer implementation. */
    std::vector<MPHit> vec(SIZE);
    for(int i = 0; i < SIZE; ++i)
    {
      vec[i].a = rand();
      vec[i].b = rand();
      vec[i].c = rand();
      vec[i].d = rand();
      vec[i].e = rand();
      vec[i].f = rand();
      vec[i].g = rand();
      vec[i].h = rand();
      vec[i].i = rand();
      vec[i].l = rand();
    }
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, vec);
    std::cerr << "Hit msgpack: " << sbuf.size() << std::endl;
}
{
  using namespace apache::thrift::protocol;
  using namespace apache::thrift::transport;
  boost::shared_ptr<TMemoryBuffer> transport(new TMemoryBuffer());
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  TFDigis digis;
  digis.a.resize(SIZE);
  for (size_t i = 0; i < SIZE; ++i)
  {
    digis.a[i].a = rand();
    digis.a[i].b = rand();
    digis.a[i].c = rand();
    digis.a[i].d = rand();
    digis.a[i].e = rand();
  }
  digis.write(protocol.get());
  std::string serialized_string = transport->getBufferAsString();
  std::cerr << "Thrift memory buffer:" << serialized_string.size() <<std::endl;

  boost::shared_ptr<TMemoryBuffer> transport2(new TMemoryBuffer());
  boost::shared_ptr<TProtocol> protocol2(new TBinaryProtocol(transport2));
  TFHits hits;
  hits.a.resize(SIZE);
  for (size_t i = 0; i < SIZE; ++i)
  {
    hits.a[i].a = rand();
    hits.a[i].b = rand();
    hits.a[i].c = rand();
    hits.a[i].d = rand();
    hits.a[i].e = rand();
    hits.a[i].f = rand();
    hits.a[i].g = rand();
    hits.a[i].h = rand();
    hits.a[i].i = rand();
    hits.a[i].l = rand();
  }
  
  hits.write(protocol2.get());
  std::string serialized_string2 = transport2->getBufferAsString();
  std::cerr << "Thrift memory buffer:" << serialized_string2.size() <<std::endl;
}
}
