#pragma once

#include "ydb_command.h"
#include "ydb_common.h"

#include <ydb/public/sdk/cpp/client/ydb_import/import.h>
#include <ydb/public/sdk/cpp/client/ydb_table/table.h>
#include <ydb/public/lib/ydb_cli/common/aws.h>
#include <ydb/public/lib/ydb_cli/common/format.h>
#include <ydb/public/lib/ydb_cli/common/parseable_struct.h>

namespace NYdb {
namespace NConsoleClient {

class TCommandImport : public TClientCommandTree {
public:
    TCommandImport();
};

class TCommandImportFromS3 : public TYdbOperationCommand,
                           public TCommandWithAwsCredentials,
                           public TCommandWithFormat {
public:
    TCommandImportFromS3();
    void Config(TConfig& config) override;
    void Parse(TConfig& config) override;
    int Run(TConfig& config) override;

private:
    struct TItemFields {
        TString Source;
        TString Destination;
    };
    DEFINE_PARSEABLE_STRUCT(TItem, TItemFields, Source, Destination);

    TString AwsEndpoint;
    ES3Scheme AwsScheme = ES3Scheme::HTTPS;
    TString AwsBucket;
    TVector<TItem> Items;
    TString Description;
    ui32 NumberOfRetries = 10;
};

class TCommandImportFromFile : public TClientCommandTree {
public:
    TCommandImportFromFile();
};

class TCommandImportFileBase : public TYdbCommand,
    public TCommandWithPath, public TCommandWithFormat {
public:
    TCommandImportFileBase(const TString& cmd, const TString& cmdDescription)
      : TYdbCommand(cmd, {}, cmdDescription)
    {}
    void Config(TConfig& config) override;
    void Parse(TConfig& config) override;

protected:
    TString FilePath; // Read from stdin if the file path is empty
    TString BytesPerRequest;
    ui64 MaxInFlightRequests = 1;
};

class TCommandImportFromCsv : public TCommandImportFileBase {
public:
    TCommandImportFromCsv(const TString& cmd = "csv", const TString& cmdDescription = "Import data from CSV file")
        : TCommandImportFileBase(cmd, cmdDescription)
    {
        InputFormat = EOutputFormat::Csv;
        Delimiter = ",";
    }
    void Config(TConfig& config) override;
    int Run(TConfig& config) override;

protected:
    TString Delimiter;
    TString NullValue;
    ui32 SkipRows = 0;
    bool Header = false;
};

class TCommandImportFromTsv : public TCommandImportFromCsv {
public:
    TCommandImportFromTsv()
        : TCommandImportFromCsv("tsv", "Import data from TSV file")
    {
        InputFormat = EOutputFormat::Tsv;
        Delimiter = "\t";
    }
};

class TCommandImportFromJson : public TCommandImportFileBase {
public:
    TCommandImportFromJson()
       : TCommandImportFileBase("json", "Import data from JSON file")
    {
        InputFormat = EOutputFormat::JsonUnicode;
    }
    void Config(TConfig& config) override;
    void Parse(TConfig& config) override;
    int Run(TConfig& config) override;
};

}
}
