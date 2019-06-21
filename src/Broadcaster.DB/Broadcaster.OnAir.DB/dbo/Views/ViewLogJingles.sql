CREATE VIEW [dbo].[ViewLogJingles]
AS
SELECT     dbo.OnAirLog.[Date], dbo.OnAirLog.ItemType, dbo.OnAirLog.ItemID, Broadcaster.dbo.ViewJinglesData_OnAir.Name AS TrackTitle, 
                      Broadcaster.dbo.ViewJinglesData_OnAir.TypeName AS ArtistName
FROM         Broadcaster.dbo.ViewJinglesData_OnAir INNER JOIN
                      dbo.OnAirLog ON Broadcaster.dbo.ViewJinglesData_OnAir.ID = dbo.OnAirLog.ItemID
WHERE     (dbo.OnAirLog.ItemType = 52)
