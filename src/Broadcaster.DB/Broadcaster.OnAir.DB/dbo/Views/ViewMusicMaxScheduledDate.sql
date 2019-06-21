
CREATE VIEW [dbo].[ViewMusicMaxScheduledDate]
AS
SELECT MAX(Date) AS MaxDate, ItemID
FROM dbo.Scheduling
WHERE (ItemType = 51)
GROUP BY ItemID

