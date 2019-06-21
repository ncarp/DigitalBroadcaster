
CREATE VIEW [dbo].[ViewJingleMaxScheduledDate]
AS
SELECT ItemType, ItemID, MAX(Date) AS MaxDate
FROM dbo.Scheduling
GROUP BY ItemType, ItemID
HAVING (ItemType = 52)

