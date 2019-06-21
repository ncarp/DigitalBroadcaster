
CREATE VIEW [dbo].[ViewCustomersNameAndID]
AS
SELECT ID, Name
FROM Customers
WHERE activ = 1



