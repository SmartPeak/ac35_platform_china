#ifndef __SECURITY_CHECK__
#define __SECURITY_CHECK__

void security_check_invalid_customer(void* param);
void security_check_temper_callback(void* param);
void security_check_unlock_callback(void* param);

int security_check_customer_entry(void);
int security_check_subapp_entry(void);
int security_check_temper_entry(void);

#endif
