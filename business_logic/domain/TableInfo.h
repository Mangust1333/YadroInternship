#ifndef TABLEINFODTO_H
#define TABLEINFODTO_H


class TableInfo {
   public:
       TableInfo(const int tableId, const int revenue, const int occupiedMinutes)
           : table_id_(tableId), revenue_(revenue), occupied_minutes_(occupiedMinutes) {}
       [[nodiscard]] int getTableId() const { return table_id_; }
       [[nodiscard]] int getRevenue() const { return revenue_; }
       [[nodiscard]] int getOccupiedMinutes() const { return occupied_minutes_; }

   private:
       int table_id_;
       int revenue_;
       int occupied_minutes_;
};

#endif //TABLEINFODTO_H
