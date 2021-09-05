#ifndef NULLABLE_H__
#define NULLABLE_H__

#define NULLABLE_ASSIGN(p_old_value_, new_value_)\
    if((p_old_value_)){ (*p_old_value_) = (new_value_); }

#endif //NULLABLE_H__