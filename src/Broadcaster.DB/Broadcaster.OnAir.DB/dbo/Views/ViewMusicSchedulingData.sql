
CREATE VIEW [dbo].[ViewMusicSchedulingData]
AS
SELECT dbo.ViewMusicMaxScheduledDate.MaxDate AS MaxMusicDate,
     dbo.ViewMusicTracks_OnAir.*, 
    dbo.ViewArtistMaxScheduledDate.MaxDate AS MaxArtistDate
FROM dbo.ViewMusicTracks_OnAir LEFT OUTER JOIN
    dbo.ViewArtistMaxScheduledDate ON 
    dbo.ViewMusicTracks_OnAir.ArtistID = dbo.ViewArtistMaxScheduledDate.ArtistID
     LEFT OUTER JOIN
    dbo.ViewMusicMaxScheduledDate ON 
    dbo.ViewMusicTracks_OnAir.TrackID = dbo.ViewMusicMaxScheduledDate.ItemID

