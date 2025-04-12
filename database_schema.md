## Схема базы данных

1. **Описание**:  
   - Таблица `ORANGERIE_USERS`: хранит имена пользователей и пароли для аутентификации.
   - Таблица `ORANGERIE_CUSTOMERS`: сведения о клиентах (ФИО, контакты, адрес).
   - Таблица `ORANGERIE_FLOWERS`: сведения о видах цветов (название, сорт, цена).
   - Таблица `ORANGERIE_COMPOSITIONS`: сведения о композициях (название и состав).
   - Таблица `ORANGERIE_COMPOSITION_FLOWERS`: связь «многие ко многим» между композициями и цветами.
   - Таблица `ORANGERIE_ORDERS`: хранит информацию о заказе (дата, количество, клиент).
   - Таблица `ORANGERIE_ORDER_PAYMENTS`: хранит рассчитанную стоимость заказа.

2. **Схема в виде изображения**:  
<img width="877" alt="db_schema" src="https://github.com/user-attachments/assets/d2fa7b6f-f753-4220-8e4d-91e6ed476a29" />

3. **SQL-скрипт создания базы**:  
   [schema.sql](https://drive.google.com/file/d/1yXxNHorHHm8Fzat1P3Q3yxe4130Gnf3U/view?usp=share_link)