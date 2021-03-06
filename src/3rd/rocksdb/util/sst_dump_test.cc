
#include <stdint.h>
#include "rocksdb/sst_dump_tool.h"

#include "rocksdb/filter_policy.h"
#include "table/block_based_table_factory.h"
#include "table/table_builder.h"
#include "util/testharness.h"
#include "util/testutil.h"

namespace rocksdb {

const uint32_t optLength = 100;

namespace {
static std::string MakeKey(int i) {
  char buf[100];
  snprintf(buf, sizeof(buf), "k_%04d", i);
  InternalKey key(std::string(buf), 0, ValueType::kTypeValue);
  return key.Encode().ToString();
}

static std::string MakeValue(int i) {
  char buf[100];
  snprintf(buf, sizeof(buf), "v_%04d", i);
  InternalKey key(std::string(buf), 0, ValueType::kTypeValue);
  return key.Encode().ToString();
}

void createSST(const std::string& file_name,
               const BlockBasedTableOptions& table_options) {
  std::shared_ptr<rocksdb::TableFactory> tf;
  tf.reset(new rocksdb::BlockBasedTableFactory(table_options));

  unique_ptr<WritableFile> file;
  Env* env = Env::Default();
  EnvOptions env_options;
  ReadOptions read_options;
  Options opts;
  const ImmutableCFOptions imoptions(opts);
  rocksdb::InternalKeyComparator ikc(opts.comparator);
  unique_ptr<TableBuilder> tb;

  env->NewWritableFile(file_name, &file, env_options);
  opts.table_factory = tf;
  std::vector<std::unique_ptr<IntTblPropCollectorFactory> >
      int_tbl_prop_collector_factories;

  tb.reset(opts.table_factory->NewTableBuilder(
      TableBuilderOptions(imoptions, ikc, &int_tbl_prop_collector_factories,
                          CompressionType::kNoCompression, CompressionOptions(),
                          false),
      file.get()));

  // Populate slightly more than 1K keys
  uint32_t num_keys = 1024;
  for (uint32_t i = 0; i < num_keys; i++) {
    tb->Add(MakeKey(i), MakeValue(i));
  }
  tb->Finish();
  file->Close();
}

void cleanup(const std::string& file_name) {
  Env* env = Env::Default();
  env->DeleteFile(file_name);
  std::string outfile_name = file_name.substr(0, file_name.length() - 4);
  outfile_name.append("_dump.txt");
  env->DeleteFile(outfile_name);
}
}  // namespace

// Test for sst dump tool "raw" mode
class SSTDumpToolTest : public testing::Test {
 public:
  BlockBasedTableOptions table_options_;

  SSTDumpToolTest() {}

  ~SSTDumpToolTest() {}
};

TEST_F(SSTDumpToolTest, EmptyFilter) {
  std::string file_name = "rocksdb_sst_test.sst";
  createSST(file_name, table_options_);

  char* usage[3];
  for (int i = 0; i < 3; i++) {
    usage[i] = new char[optLength];
  }
  snprintf(usage[0], optLength, "./sst_dump");
  snprintf(usage[1], optLength, "--command=raw");
  snprintf(usage[2], optLength, "--file=rocksdb_sst_test.sst");

  rocksdb::SSTDumpTool tool;
  ASSERT_TRUE(!tool.Run(3, usage));

  cleanup(file_name);
  for (int i = 0; i < 3; i++) {
    delete[] usage[i];
  }
}

TEST_F(SSTDumpToolTest, FilterBlock) {
  table_options_.filter_policy.reset(rocksdb::NewBloomFilterPolicy(10, true));
  std::string file_name = "rocksdb_sst_test.sst";
  createSST(file_name, table_options_);

  char* usage[3];
  for (int i = 0; i < 3; i++) {
    usage[i] = new char[optLength];
  }
  snprintf(usage[0], optLength, "./sst_dump");
  snprintf(usage[1], optLength, "--command=raw");
  snprintf(usage[2], optLength, "--file=rocksdb_sst_test.sst");

  rocksdb::SSTDumpTool tool;
  ASSERT_TRUE(!tool.Run(3, usage));

  cleanup(file_name);
  for (int i = 0; i < 3; i++) {
    delete[] usage[i];
  }
}

TEST_F(SSTDumpToolTest, FullFilterBlock) {
  table_options_.filter_policy.reset(rocksdb::NewBloomFilterPolicy(10, false));
  std::string file_name = "rocksdb_sst_test.sst";
  createSST(file_name, table_options_);

  char* usage[3];
  for (int i = 0; i < 3; i++) {
    usage[i] = new char[optLength];
  }
  snprintf(usage[0], optLength, "./sst_dump");
  snprintf(usage[1], optLength, "--command=raw");
  snprintf(usage[2], optLength, "--file=rocksdb_sst_test.sst");

  rocksdb::SSTDumpTool tool;
  ASSERT_TRUE(!tool.Run(3, usage));

  cleanup(file_name);
  for (int i = 0; i < 3; i++) {
    delete[] usage[i];
  }
}

TEST_F(SSTDumpToolTest, GetProperties) {
  table_options_.filter_policy.reset(rocksdb::NewBloomFilterPolicy(10, false));
  std::string file_name = "rocksdb_sst_test.sst";
  createSST(file_name, table_options_);

  char* usage[3];
  for (int i = 0; i < 3; i++) {
    usage[i] = new char[optLength];
  }
  snprintf(usage[0], optLength, "./sst_dump");
  snprintf(usage[1], optLength, "--show_properties");
  snprintf(usage[2], optLength, "--file=rocksdb_sst_test.sst");

  rocksdb::SSTDumpTool tool;
  ASSERT_TRUE(!tool.Run(3, usage));

  cleanup(file_name);
  for (int i = 0; i < 3; i++) {
    delete[] usage[i];
  }
}
}  // namespace rocksdb

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
