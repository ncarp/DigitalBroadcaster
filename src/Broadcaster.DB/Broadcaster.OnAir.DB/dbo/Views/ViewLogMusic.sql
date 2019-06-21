CREATE VIEW [dbo].[ViewLogMusic]
AS
SELECT     dbo.OnAirLog.[Date], dbo.OnAirLog.ItemType, dbo.OnAirLog.ItemID, dbo.ViewMusicTracks_OnAir.TrackTitle, 
                      dbo.ViewMusicTracks_OnAir.ArtistName
FROM         dbo.OnAirLog INNER JOIN
                      dbo.ViewMusicTracks_OnAir ON dbo.OnAirLog.ItemID = dbo.ViewMusicTracks_OnAir.TrackID
WHERE     (dbo.OnAirLog.ItemType = 51)
