#pragma once

#include "common/smart_ptr.h"

#include "core/connection_types.h"
#include "core/ssh_info.h"

namespace fastoredis
{
    class IConnectionSettingsBase
    {
    public:
        virtual ~IConnectionSettingsBase();
        std::string hash() const;

        std::string loggingPath() const;

        virtual std::string commandLine() const = 0;
        virtual void setCommandLine(const std::string& line) = 0;

        virtual std::string host() const = 0;
        virtual int port() const = 0;
        virtual void setPort(int port) = 0;

        std::string fullAddress() const;

        std::string connectionName() const;
        void setConnectionName(const std::string &name);

        connectionTypes connectionType() const;
        static IConnectionSettingsBase* createFromType(connectionTypes type, const std::string& conName = std::string());
        static IConnectionSettingsBase* fromString(const std::string& val);
        std::string toString() const;

        virtual IConnectionSettingsBase* clone() const = 0;

        bool loggingEnabled() const;
        void setLoggingEnabled(bool isLogging);

        uint32_t loggingMsTimeInterval() const;

        SSHInfo sshInfo() const;
        void setSshInfo(const SSHInfo& info);

    protected:
        virtual std::string toCommandLine() const = 0;
        virtual void initFromCommandLine(const std::string& val) = 0;
        IConnectionSettingsBase(const std::string& connectionName, connectionTypes type);

    private:
        std::string connectionName_;
        std::string hash_;
        bool logging_enabled_;
        SSHInfo sshInfo_;
        const connectionTypes type_;
    };

    const char *useHelpText(connectionTypes type);
    std::string defaultCommandLine(connectionTypes type);

    typedef common::shared_ptr<IConnectionSettingsBase> IConnectionSettingsBaseSPtr;
}
