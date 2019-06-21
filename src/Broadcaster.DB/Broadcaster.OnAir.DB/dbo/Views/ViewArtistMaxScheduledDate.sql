
CREATE VIEW [dbo].[ViewArtistMaxScheduledDate]
AS
SELECT MAX(Date) AS MaxDate, ItemParentID AS ArtistID
FROM dbo.Scheduling
WHERE (ItemType = 51)
GROUP BY ItemParentID

