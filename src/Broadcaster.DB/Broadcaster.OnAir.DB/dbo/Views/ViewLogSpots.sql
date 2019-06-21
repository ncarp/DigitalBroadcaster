CREATE VIEW [dbo].[ViewLogSpots]
AS
SELECT     dbo.OnAirLog.[Date], dbo.OnAirLog.ItemType, dbo.OnAirLog.ItemID, Broadcaster.dbo.ViewSpotInfo.Name AS TrackTitle, 
                      Broadcaster.dbo.ViewSpotInfo.CustomerName AS ArtistName
FROM         dbo.OnAirLog INNER JOIN
                      Broadcaster.dbo.ViewSpotInfo ON dbo.OnAirLog.ItemID = Broadcaster.dbo.ViewSpotInfo.ID
WHERE     (dbo.OnAirLog.ItemType = 53)
