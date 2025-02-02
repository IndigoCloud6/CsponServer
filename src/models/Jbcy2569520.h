/**
 *
 *  Jbcy2569520.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/BaseBuilder.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace maxyun
{

class Jbcy2569520
{
  public:
    struct Cols
    {
        static const std::string _objectid;
        static const std::string _bsm;
        static const std::string _ysdm;
        static const std::string _xzqdm;
        static const std::string _xzqmc;
        static const std::string _mc;
        static const std::string _lx;
        static const std::string _cdjb;
        static const std::string _mj;
        static const std::string _ccl;
        static const std::string _zxl;
        static const std::string _bz;
        static const std::string _cddb;
        static const std::string _shape_length;
        static const std::string _shape_area;
        static const std::string _shape;
    };

    static const int primaryKeyNumber;
    static const std::string tableName;
    static const bool hasPrimaryKey;
    static const std::string primaryKeyName;
    using PrimaryKeyType = int32_t;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names,
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all
     * columns by an asterisk), please set the offset to -1.
     */
    explicit Jbcy2569520(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Jbcy2569520(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Jbcy2569520(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Jbcy2569520() = default;

    void updateByJson(const Json::Value &pJson) noexcept(false);
    void updateByMasqueradedJson(const Json::Value &pJson,
                                 const std::vector<std::string> &pMasqueradingVector) noexcept(false);
    static bool validateJsonForCreation(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForCreation(const Json::Value &,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                    std::string &err);
    static bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForUpdate(const Json::Value &,
                                          const std::vector<std::string> &pMasqueradingVector,
                                          std::string &err);
    static bool validJsonOfField(size_t index,
                          const std::string &fieldName,
                          const Json::Value &pJson,
                          std::string &err,
                          bool isForCreation);

    /**  For column objectid  */
    ///Get the value of the column objectid, returns the default value if the column is null
    const int32_t &getValueOfObjectid() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getObjectid() const noexcept;
    ///Set the value of the column objectid
    void setObjectid(const int32_t &pObjectid) noexcept;

    /**  For column bsm  */
    ///Get the value of the column bsm, returns the default value if the column is null
    const std::string &getValueOfBsm() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getBsm() const noexcept;
    ///Set the value of the column bsm
    void setBsm(const std::string &pBsm) noexcept;
    void setBsm(std::string &&pBsm) noexcept;
    void setBsmToNull() noexcept;

    /**  For column ysdm  */
    ///Get the value of the column ysdm, returns the default value if the column is null
    const std::string &getValueOfYsdm() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getYsdm() const noexcept;
    ///Set the value of the column ysdm
    void setYsdm(const std::string &pYsdm) noexcept;
    void setYsdm(std::string &&pYsdm) noexcept;
    void setYsdmToNull() noexcept;

    /**  For column xzqdm  */
    ///Get the value of the column xzqdm, returns the default value if the column is null
    const std::string &getValueOfXzqdm() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getXzqdm() const noexcept;
    ///Set the value of the column xzqdm
    void setXzqdm(const std::string &pXzqdm) noexcept;
    void setXzqdm(std::string &&pXzqdm) noexcept;
    void setXzqdmToNull() noexcept;

    /**  For column xzqmc  */
    ///Get the value of the column xzqmc, returns the default value if the column is null
    const std::string &getValueOfXzqmc() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getXzqmc() const noexcept;
    ///Set the value of the column xzqmc
    void setXzqmc(const std::string &pXzqmc) noexcept;
    void setXzqmc(std::string &&pXzqmc) noexcept;
    void setXzqmcToNull() noexcept;

    /**  For column mc  */
    ///Get the value of the column mc, returns the default value if the column is null
    const std::string &getValueOfMc() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getMc() const noexcept;
    ///Set the value of the column mc
    void setMc(const std::string &pMc) noexcept;
    void setMc(std::string &&pMc) noexcept;
    void setMcToNull() noexcept;

    /**  For column lx  */
    ///Get the value of the column lx, returns the default value if the column is null
    const std::string &getValueOfLx() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getLx() const noexcept;
    ///Set the value of the column lx
    void setLx(const std::string &pLx) noexcept;
    void setLx(std::string &&pLx) noexcept;
    void setLxToNull() noexcept;

    /**  For column cdjb  */
    ///Get the value of the column cdjb, returns the default value if the column is null
    const std::string &getValueOfCdjb() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getCdjb() const noexcept;
    ///Set the value of the column cdjb
    void setCdjb(const std::string &pCdjb) noexcept;
    void setCdjb(std::string &&pCdjb) noexcept;
    void setCdjbToNull() noexcept;

    /**  For column mj  */
    ///Get the value of the column mj, returns the default value if the column is null
    const double &getValueOfMj() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<double> &getMj() const noexcept;
    ///Set the value of the column mj
    void setMj(const double &pMj) noexcept;
    void setMjToNull() noexcept;

    /**  For column ccl  */
    ///Get the value of the column ccl, returns the default value if the column is null
    const double &getValueOfCcl() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<double> &getCcl() const noexcept;
    ///Set the value of the column ccl
    void setCcl(const double &pCcl) noexcept;
    void setCclToNull() noexcept;

    /**  For column zxl  */
    ///Get the value of the column zxl, returns the default value if the column is null
    const double &getValueOfZxl() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<double> &getZxl() const noexcept;
    ///Set the value of the column zxl
    void setZxl(const double &pZxl) noexcept;
    void setZxlToNull() noexcept;

    /**  For column bz  */
    ///Get the value of the column bz, returns the default value if the column is null
    const std::string &getValueOfBz() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getBz() const noexcept;
    ///Set the value of the column bz
    void setBz(const std::string &pBz) noexcept;
    void setBz(std::string &&pBz) noexcept;
    void setBzToNull() noexcept;

    /**  For column cddb  */
    ///Get the value of the column cddb, returns the default value if the column is null
    const std::string &getValueOfCddb() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getCddb() const noexcept;
    ///Set the value of the column cddb
    void setCddb(const std::string &pCddb) noexcept;
    void setCddb(std::string &&pCddb) noexcept;
    void setCddbToNull() noexcept;

    /**  For column shape_length  */
    ///Get the value of the column shape_length, returns the default value if the column is null
    const double &getValueOfShapeLength() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<double> &getShapeLength() const noexcept;
    ///Set the value of the column shape_length
    void setShapeLength(const double &pShapeLength) noexcept;
    void setShapeLengthToNull() noexcept;

    /**  For column shape_area  */
    ///Get the value of the column shape_area, returns the default value if the column is null
    const double &getValueOfShapeArea() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<double> &getShapeArea() const noexcept;
    ///Set the value of the column shape_area
    void setShapeArea(const double &pShapeArea) noexcept;
    void setShapeAreaToNull() noexcept;

    /**  For column shape  */
    ///Get the value of the column shape, returns the default value if the column is null
    const std::string &getValueOfShape() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getShape() const noexcept;
    ///Set the value of the column shape
    void setShape(const std::string &pShape) noexcept;
    void setShape(std::string &&pShape) noexcept;
    void setShapeToNull() noexcept;


    static size_t getColumnNumber() noexcept {  return 16;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
    /// Relationship interfaces
  private:
    friend drogon::orm::Mapper<Jbcy2569520>;
    friend drogon::orm::BaseBuilder<Jbcy2569520, true, true>;
    friend drogon::orm::BaseBuilder<Jbcy2569520, true, false>;
    friend drogon::orm::BaseBuilder<Jbcy2569520, false, true>;
    friend drogon::orm::BaseBuilder<Jbcy2569520, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Jbcy2569520>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> objectid_;
    std::shared_ptr<std::string> bsm_;
    std::shared_ptr<std::string> ysdm_;
    std::shared_ptr<std::string> xzqdm_;
    std::shared_ptr<std::string> xzqmc_;
    std::shared_ptr<std::string> mc_;
    std::shared_ptr<std::string> lx_;
    std::shared_ptr<std::string> cdjb_;
    std::shared_ptr<double> mj_;
    std::shared_ptr<double> ccl_;
    std::shared_ptr<double> zxl_;
    std::shared_ptr<std::string> bz_;
    std::shared_ptr<std::string> cddb_;
    std::shared_ptr<double> shapeLength_;
    std::shared_ptr<double> shapeArea_;
    std::shared_ptr<std::string> shape_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[16]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where objectid = $1";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where objectid = $1";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
            sql += "objectid,";
            ++parametersCount;
        if(dirtyFlag_[1])
        {
            sql += "bsm,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "ysdm,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "xzqdm,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "xzqmc,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "mc,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "lx,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "cdjb,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "mj,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "ccl,";
            ++parametersCount;
        }
        if(dirtyFlag_[10])
        {
            sql += "zxl,";
            ++parametersCount;
        }
        if(dirtyFlag_[11])
        {
            sql += "bz,";
            ++parametersCount;
        }
        if(dirtyFlag_[12])
        {
            sql += "cddb,";
            ++parametersCount;
        }
        if(dirtyFlag_[13])
        {
            sql += "shape_length,";
            ++parametersCount;
        }
        if(dirtyFlag_[14])
        {
            sql += "shape_area,";
            ++parametersCount;
        }
        if(dirtyFlag_[15])
        {
            sql += "shape,";
            ++parametersCount;
        }
        needSelection=true;
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        int placeholder=1;
        char placeholderStr[64];
        size_t n=0;
        sql +="default,";
        if(dirtyFlag_[1])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[2])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[3])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[4])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[5])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[6])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[7])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[8])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[9])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[10])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[11])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[12])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[13])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[14])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[15])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        if(needSelection)
        {
            sql.append(") returning *");
        }
        else
        {
            sql.append(1, ')');
        }
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace maxyun
} // namespace drogon_model
