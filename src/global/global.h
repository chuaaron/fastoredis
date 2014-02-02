#pragma once

#include <string>
#include <vector>

#include "common/boost_extension.hpp"
#include "common/value.h"

namespace fastoredis
{
    enum supportedViews
    {
        Tree = 0,
        Table,
        Text
    };

    std::string toStdString(supportedViews v);
    supportedViews toSupportedViews(const std::string &text);
    std::vector<std::string> allSupportedViews();

    class FastoObject;

    typedef boost::intrusive_ptr<FastoObject> FastoObjectPtr;

    std::string toStdString(const FastoObjectPtr &obj);

    class FastoObject
            : public common::boost_extension::intrusive_ptr_base<FastoObject>
    {
	public:
		typedef std::vector<FastoObjectPtr> child_container_type;

        FastoObject(const FastoObjectPtr &parent, common::Value *val);
        ~FastoObject();
        common::Value::Type type() const;
        std::string toStdString() const;
        const char *c_str() const;

		child_container_type childrens() const;
        static FastoObjectPtr createRoot(const std::string& text = std::string());
		void addChildren(const FastoObjectPtr &child);
        bool isRoot() const;

    private:
		DISALLOW_COPY_AND_ASSIGN(FastoObject);

        const FastoObjectPtr parent_;
		child_container_type childrens_;

        boost::scoped_ptr<common::Value> value_;
    };
}
